#ifndef SETDIFFERENCE_H
#define SETDIFFERENCE_H

#include "bloomfilter.h"

class SetDifference
{
public:
    static int estimateCount( const BloomFilter& set );

    static BloomFilter* difference( const BloomFilter& set1, const BloomFilter& set2 );

    int methodOne( BloomFilter& set1, BloomFilter& set2 );



};

#endif // SETDIFFERENCE_H
