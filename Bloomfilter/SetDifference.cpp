#include "SetDifference.h"
#include <iostream>
#include <QtMath>
#include <QTime>
#include <QException>
#include <QDebug>

// Returned Value needs to be deleted after use
// Returns A-B
BloomFilter* SetDifference::filterSubtraction( const BloomFilter& setA, const BloomFilter& setB )
{
    if(setA.m_numBits != setB.m_numBits || setA.m_numHash != setB.m_numHash)
    {
        qDebug() << "Uncompatible BloomFilters";
        return nullptr;
    }

    BloomFilter* output = new BloomFilter(setA.m_numBits, setA.m_numHash);

    for(int i=0; i<setA.m_numBits; ++i)
        output->m_filter.setBit(i, (setA.m_filter.at(i) - setB.m_filter.at(i)) > 0 ? 1 : 0);

    return output;
}

// Returned Value needs to be deleted after use
// Returns A-B
CountBloomFilter* SetDifference::filterSubtraction( const CountBloomFilter& set1, const CountBloomFilter& set2 )
{
    if(set1.m_numBits != set2.m_numBits || set1.m_numHash != set2.m_numHash)
    {
        qDebug() << "Invalid BloomFilters";
        return nullptr;
    }

    CountBloomFilter* output = new CountBloomFilter(set1.m_numBits, set1.m_numHash);

    for(int i=0; i<set1.m_numBits; ++i)
        output->m_filter[i] = (set1.m_filter[i] - set2.m_filter[i] > 0) ? set1.m_filter[i] - set2.m_filter[i] : 0;

    return output;
}

// Base line template for Calculating differences
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

// Method One for Regular BloomFilters
SetDifference::Answer SetDifference::methodOne( const BloomFilter& set1, const BloomFilter& set2 )
{
    QTime time;
    time.start();
    SetDifference::Answer answer;

    // Find set Difference
    BloomFilter* diff1 = filterSubtraction(set1, set2);

    // Count The set bits
    double setBits = 0;
    for(int i=0; i < diff1->m_filter.size(); ++i)
        setBits += diff1->m_filter[i];

    double k = set1.m_numHash;
    double m = set1.m_numBits;
    double n = set2.m_numElements;

    double x = setBits / m;

    // Do the Math
    int u = round((log(pow(((m - 1.0)/m),(k* n)) - x) - k*n*log((m - 1.0)/m))/(k*log((m - 1.0)/m)));

    //Set Answers
    answer.set1 = u;
    answer.time = time.elapsed();

    delete diff1;
    return answer;
}

// Method Two for Regular BloomFilters
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

SetDifference::Answer SetDifference::methodOne( const CountBloomFilter& set1, const CountBloomFilter& set2 )
{
    QTime time;
    time.start();
    SetDifference::Answer answer;

    // Find set Difference
    CountBloomFilter* diff1 = SetDifference::filterSubtraction(set1, set2);

    answer.set1 = 0;
    for(int i=0; i < diff1->m_numBits; ++i)
        answer.set1 += diff1->m_filter[i];

    answer.set1 = answer.set1 / set1.m_numHash;
    answer.time = time.elapsed();
    return answer;
}

SetDifference::Answer SetDifference::methodTwo( const QList<QString>& set1, const CountBloomFilter& set2 )
{
    QTime time;
    time.start();
    SetDifference::Answer answer;

    //Copy List for local Modification
    QList<QString> temp;

    for(QString item : set1)
    {
        if(!temp.count(item))
        {
            int diff = set1.count(item) - set2.testElement(item);
//            printf("%d:%d,", diff, set2.testElement(item));
            answer.set1 += (diff > 0 ? diff : 0);
            temp.append(item);
        }
    }

    answer.time = time.elapsed();
    return answer;
}
