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

// Returned Value needs to be deleted after use
BloomFilter* SetDifference::filterSub( const BloomFilter& set1, const BloomFilter& set2 )
{
    if(set1.m_numBits != set2.m_numBits || set1.m_numHash != set2.m_numHash)
    {
        qDebug() << "Invalid BloomFilters";
        return nullptr;
    }

    BloomFilter* output = new BloomFilter(set1.m_numBits, set1.m_numHash);

    for(int i=0; i<set1.m_numBits; ++i)
    {
        output->m_filter.setBit(i, (set1.m_filter.at(i) - set2.m_filter.at(i)) > 0 ? 1 : 0);
    }
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

    for(QString a : set2)
        if(!set1.contains(a))
            answer.set2 += 1;

    answer.time = time.elapsed();
    return answer;
}

SetDifference::Answer SetDifference::methodOne( const BloomFilter& set1, const BloomFilter& set2 )
{
    QTime time;
    time.start();

    SetDifference::Answer answer;

    BloomFilter* diff1 = filterSub(set1, set2);
    BloomFilter* diff2 = filterSub(set2, set1);

    answer.set1 = estimateCount(*diff1);
    answer.set2 = estimateCount(*diff2);

    delete diff1;
    delete diff2;

    answer.time = time.elapsed();
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

    answer.set2 = std::abs((set1.size() - estimateCount(set2)) - answer.set1);
    answer.time = time.elapsed();
    return answer;
}