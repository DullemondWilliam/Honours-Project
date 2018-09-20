#include <QCoreApplication>
#include "CountBloomFilter.h"
#include "bloomfilter.h"
#include "MurmurHash3.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BloomFilter bf = BloomFilter(1000000, 4);

    for(int i=0; i<100; ++i)
        bf.addElement(QString::number(rand() % 10000));

    for(int i=0; i<10000; ++i)
        if(bf.testElement(QString::number(i)))
            std::cout << i << std::endl;

    CountBloomFilter cbf = CountBloomFilter(1000000, 4);

    for(int i=0; i<1000; ++i)
        cbf.addElement(QString::number(rand() % 100));

    for(int i=0; i<10000; ++i)
    {
        int count = cbf.testElement(QString::number(i));
        if(count)
            std::cout << i << " : " << count << std::endl;
    }

    return a.exec();
}
