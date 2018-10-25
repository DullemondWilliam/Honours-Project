#include "SetDifference.h"
#include <iostream>
#include <QtMath>
#include <QException>
#include <QDebug>

int SetDifference::estimateCount( const BloomFilter& set )
{
    int x = set.m_filter.count(1);
    int n = -1.0 * ((float)set.m_numBits/(float)set.m_numHash) * qLn(1 - ((float)x/(float)set.m_numBits));
    return n;
}

BloomFilter* SetDifference::difference( const BloomFilter& set1, const BloomFilter& set2 )
{
    if(set1.m_numBits != set2.m_numBits || set1.m_numHash != set2.m_numHash)
    {
        qDebug() << "Invalid BloomFilters";
        return 0;
    }

    BloomFilter* output = new BloomFilter(set1.m_numBits, set1.m_numHash);

    for(int i=0; i<set1.m_numBits; ++i)
        output->m_filter.setBit(i, (set1.m_filter.at(i) ^ set2.m_filter.at(i)));

    return output;
}
