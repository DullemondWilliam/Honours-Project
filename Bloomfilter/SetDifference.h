#ifndef SETDIFFERENCE_H
#define SETDIFFERENCE_H

#include "Bloomfilter.h"
#include "CountBloomFilter.h"
#include <QList>
#include <QPair>
class SetDifference
{
public:

    struct Answer {
      int set1 = 0;
      int set2 = 0;
      int time = 0;
      int bytesComm = 0;
    };

    static BloomFilter* filterSubtraction( const BloomFilter& set1, const BloomFilter& set2 );
    static CountBloomFilter* filterSubtraction( const CountBloomFilter& set1, const CountBloomFilter& set2 );


    static Answer setDifference( QList<QString> set1, QList<QString> set2 );

    static SetDifference::Answer methodOne( const BloomFilter& set1, const BloomFilter& set2 );
    static SetDifference::Answer methodTwo( const QList<QString>& setContent, BloomFilter& set2 );

    static SetDifference::Answer methodOne( const CountBloomFilter& set1, const CountBloomFilter& set2 );
    static SetDifference::Answer methodTwo( const QList<QString>& setContent, const CountBloomFilter& set2 );
};

#endif // SETDIFFERENCE_H
