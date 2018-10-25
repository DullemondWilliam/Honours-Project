#include <QCoreApplication>
#include "CountBloomFilter.h"
#include "bloomfilter.h"
#include "MurmurHash3.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include "SetDifference.h"
#include <time.h>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    srand(time(NULL));

    BloomFilter bf1 = BloomFilter(1000000, 4);
    BloomFilter bf2 = BloomFilter(1000000, 4);


    for(int i=0; i<100; ++i)
    {
        bf1.addElement(QString::number(rand() % 10000));
        bf2.addElement(QString::number(rand() % 10000));
    }
    BloomFilter* diff = SetDifference::difference(bf1, bf2);

    std::cout << "Test Set" << std::endl;
    for(int i=0; i<10000; ++i)
        if(bf1.testElement(QString::number(i)))
            std::cout << i << std::endl;

    std::cout << "Test Diff" << std::endl;
    for(int i=0; i<10000; ++i)
        if(diff->testElement(QString::number(i)))
            std::cout << i << std::endl;

//    CountBloomFilter cbf = CountBloomFilter(1000000, 4);

//    for(int i=0; i<1000; ++i)
//        cbf.addElement(QString::number(rand() % 100));

//    for(int i=0; i<10000; ++i)
//    {
//        int count = cbf.testElement(QString::number(i));
//        if(count)
//            std::cout << i << " : " << count << std::endl;
//    }

    return 0;// a.exec();
}
