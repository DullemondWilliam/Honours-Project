#include "SetDifference.h"
#include <iostream>
#include <QtMath>
#include <QTime>
#include <QException>
#include <QDebug>

int SetDifference::estimateCount( const BloomFilter& set )
{
    int x = set.m_filter.count(1);
    int n = -1.0 * ((float)set.m_numBits/(float)set.m_numHash) * qLn(1 - ((float)x/(float)set.m_numBits));
    return n;
}

int SetDifference::estimateCount( const CountBloomFilter& set )
{
    int count = 0;
    for(char i: set.m_filter)
        count += i;
    return count / set.m_numHash;
}


// Returned Value needs to be deleted after use
BloomFilter* SetDifference::filterSub( const BloomFilter& setA, const BloomFilter& setB )
{
    if(setA.m_numBits != setB.m_numBits || setA.m_numHash != setB.m_numHash)
    {
        qDebug() << "Invalid BloomFilters";
        return nullptr;
    }

    BloomFilter* output = new BloomFilter(setA.m_numBits, setA.m_numHash);

    for(int i=0; i<setA.m_numBits; ++i)
        output->m_filter.setBit(i, (setA.m_filter.at(i) - setB.m_filter.at(i)) > 0 ? 1 : 0);
//        output->m_filter.setBit(i, (setA.m_filter.at(i) & (!setB.m_filter.at(i))));

    return output;
}

// Returned Value needs to be deleted after use
CountBloomFilter* SetDifference::filterSub( const CountBloomFilter& set1, const CountBloomFilter& set2 )
{
    if(set1.m_numBits != set2.m_numBits || set1.m_numHash != set2.m_numHash)
    {
        qDebug() << "Invalid BloomFilters";
        return nullptr;
    }

    CountBloomFilter* output = new CountBloomFilter(set1.m_numBits, set1.m_numHash);

//    for(int i=0; i<set1.m_numBits; ++i)
//    {
//        output->m_filter.setBit(i, (set1.m_filter.at(i) - set2.m_filter.at(i)) > 0 ? 1 : 0);
//    }
    return output;
}

SetDifference::Answer SetDifference::setDifference( QList<QString> set1, QList<QString> set2 )
{
    QTime time;
    time.start();

    SetDifference::Answer answer;

    for(QString a : set1)
        if(!set2.contains(a))
            answer.set1 += 1;

    answer.time = time.elapsed();
    return answer;
}


SetDifference::Answer SetDifference::methodOne( const BloomFilter& set1, const BloomFilter& set2 )
{
    QTime time;
    time.start();
    SetDifference::Answer answer;

    // Find Ratio
    double ratio = 0;
    for(int i=0; i < set1.m_filter.size(); ++i)
        ratio += set1.m_filter[i];
    ratio = (set1.m_numElements * set1.m_numHash) / ratio;

    //printf("%d x %d = %lf ~ %lf\n", set1.m_numElements, set1.m_numHash, ratio, ratio * 1.5);
    ratio = ratio * ratio;

    // Find set Difference
    BloomFilter* diff1 = filterSub(set1, set2);

    // Count The Difference count
    double setBits = 0;
    for(int i=0; i < diff1->m_filter.size(); ++i)
        setBits += diff1->m_filter[i];

    //printf("(%lf * %lf)/%d = %lf\n", setBits, ratio, set1.m_numHash, (setBits * ratio)/ (double)set1.m_numHash);

    //Set Answers
    answer.set1 = (setBits * ratio)/ (double)set1.m_numHash;
    answer.time = time.elapsed();

    delete diff1;
    return answer;
}

SetDifference::Answer SetDifference::methodTwo( const QList<QString>& set1, BloomFilter& set2 )
{
    QTime time;
    time.start();

    SetDifference::Answer answer;

    for(QString item : set1)
        if( !set2.testElement(item) )
            answer.set1 += 1;

    answer.time = time.elapsed();
    return answer;
}
