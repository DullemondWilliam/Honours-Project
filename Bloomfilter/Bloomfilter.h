#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <QList>
#include <QDebug>
#include <QByteArray>
#include <QBitArray>
#include <QCryptographicHash>

class BloomFilter
{
public:
    BloomFilter( int numBits, int numHash );
    ~BloomFilter();

    bool testElement( const QString& test );
    bool addElement( const QString& add );

    QByteArray xorByteArray( const QByteArray& a1, const QByteArray& a2 );
    void  printFilter();

    QBitArray m_filter;

    int m_numBits;
    int m_numHash;
    int m_numElements;

    double m_sectionSize;
    double m_fraction;

};

#endif // BLOOMFILTER_H
