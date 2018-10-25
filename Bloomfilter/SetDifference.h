#ifndef SETDIFFERENCE_H
#define SETDIFFERENCE_H

#include "Bloomfilter.h"
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

    static int estimateCount( const BloomFilter& set );
    static BloomFilter* filterSub( const BloomFilter& set1, const BloomFilter& set2 );
    static Answer setDifference( QList<QString> set1, QList<QString> set2 );

    static SetDifference::Answer methodOne( const BloomFilter& set1, const BloomFilter& set2 );
    static SetDifference::Answer methodTwo( const QList<QString>& setContent, BloomFilter& set2 );


};

#endif // SETDIFFERENCE_H
