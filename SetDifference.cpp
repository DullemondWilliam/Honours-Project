#include "SetDifference.h"
#include <iostream>
#include <QtMath>

int SetDifference::estimateCount( const BloomFilter& set )
{
    int x = set.m_filter.count(1);
    int n = -1.0 * ((float)set.m_numBits/(float)set.m_numHash) * qLn(1 - ((float)x/(float)set.m_numBits));
    return n;
}
