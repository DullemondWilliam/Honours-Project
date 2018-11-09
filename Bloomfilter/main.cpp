#include <QCoreApplication>
#include "CountBloomFilter.h"
#include "Bloomfilter.h"
#include "MurmurHash3.h"
#include <stdlib.h>     /* srand, rand */
#include "SetDifference.h"
#include <time.h>
#include <iostream>
#include <string>
#include "Controller.h"

using namespace std;

void generateSets( QList<QString>& set1, QList<QString>& set2);

int main(int argc, char *argv[])
{
    srand(uint(time(nullptr)));


    if(argc == 1)
        cout << "Give me some varibles you wanker" << endl;
    else if( !strcmp( argv[1],"-b") )
        Controller::testCommBloomFilter(argc, argv);
    else if( !strcmp( argv[1],"-c") )
        Controller::testCommCountBloomFilter(argc, argv);
    else if( !strcmp( argv[1],"-bt") )
        Controller::testBloomFilter(argc, argv);
    else if( !strcmp( argv[1],"-ct") )
        Controller::testCountBloomFilter(argc, argv);

    // optimialNumberOfHashes(int expectedSetSize, int filterSize)

    //QCoreApplication a(argc, argv);

    //Usage
    // ./Honours FilterSize HashSize set1Size set2Size set1Diff



//    CountBloomFilter cbf1 = CountBloomFilter(100000, 4);
//    CountBloomFilter cbf2 = CountBloomFilter(100000, 4);
//    CountBloomFilter cbf3 = CountBloomFilter(100000, 4);
//    CountBloomFilter cbf4 = CountBloomFilter(100000, 4);

//    for(int i=0; i<10000; ++i)
//    {
//        cbf1.addElement(QString::number(rand() % 10));
//        cbf2.addElement(QString::number(rand() % 100));
//        cbf3.addElement(QString::number(rand() % 1000));
//        cbf4.addElement(QString::number(rand() % 10000));
//    }
//    cout << SetDifference::estimateCount(cbf1) << endl;
//    cout << SetDifference::estimateCount(cbf2) << endl;
//    cout << SetDifference::estimateCount(cbf3) << endl;
//    cout << SetDifference::estimateCount(cbf4) << endl;



//    return 0;
    // a.exec();
}
