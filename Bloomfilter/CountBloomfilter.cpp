#include "CountBloomFilter.h"
#include "math.h"
#include <QDebug>
#include <qmath.h>
#include "bitset"
#include "MurmurHash3.h"

namespace
{
    // number of bits in hashes
    const int numberOfBits = 32;
}

CountBloomFilter::CountBloomFilter( int numBits, int numHash ):
    m_numBits( numBits ),
    m_numHash( numHash ),
    m_numElements( 0 )
{
//    qInfo() << " Number of Storage bits: " << m_numBits;
//    qInfo() << " Number of Hash bits: " << m_numHash;
    m_filter = QByteArray( m_numBits, 0 );
    m_fraction = m_numBits / qPow (2,numberOfBits);
}

CountBloomFilter::~CountBloomFilter()
{
}

// Test an element against the CountBloomFilter
int CountBloomFilter::testElement( QString test ) const
{
    uint32_t num;

    // Create and test K hashes with predictable seeds
    int lowestNumber = -1;
    for( int i=0; i < m_numHash; ++i )
    {
        MurmurHash3_x86_32( test.toLocal8Bit().data(), test.size(), i, &num );

        double index = m_fraction * num;
        if( lowestNumber == -1 || m_filter.at( index ) < lowestNumber )
            lowestNumber = m_filter.at( index );
    }
    return lowestNumber;
}

// Add an element to the CountBloomFilter
int CountBloomFilter::addElement( QString add )
{
    uint32_t num;

    // Create and test K hashes with predictable seeds
    int lowestNumber = -1;
    for( int i=0; i < m_numHash; ++i )
    {
        MurmurHash3_x86_32( add.toLocal8Bit().data(), add.size(), i, &num );

        double index = m_fraction * num;
        if( lowestNumber == -1 || m_filter.at( index ) < lowestNumber )
            lowestNumber = m_filter.at( index );

        // Update
        m_filter.insert(index, m_filter.at( index ) + 1);
    }
    return lowestNumber;
}

// Remove an element from the CountBloomFilter
int CountBloomFilter::removeElement( QString remove )
{
    uint32_t num;

    // Create and test K hashes with predictable seeds
    int lowestNumber = -1;
    for( int i=0; i < m_numHash; ++i )
    {
        MurmurHash3_x86_32( remove.toLocal8Bit().data(), remove.size(), i, &num );

        double index = qFloor( m_fraction * num );
        m_filter.insert(index, m_filter.at( index ) - 1);
        if( m_filter.at( index ) < lowestNumber || lowestNumber  == -1 )
            lowestNumber = m_filter.at( index );

    }
    return lowestNumber;
}

void CountBloomFilter::printFilter() const
{
    for( int i=m_numBits-1 ; i >= 0 ; --i )
        printf("%d,", m_filter[i]);
    printf("\n");
}

