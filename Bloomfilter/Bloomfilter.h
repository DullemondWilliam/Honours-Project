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

    void  printFilter() const;

    QBitArray m_filter;

    int m_numBits;
    int m_numHash;
    int m_numElements;

    double m_sectionSize;
    double m_fraction;  // Fraction allows the hashes to be divided by M

};

#endif // BLOOMFILTER_H
