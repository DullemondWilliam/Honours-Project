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

//Usage
// ./Honours type FilterSize HashSize set1Size set2Size set1Diff

int main(int argc, char *argv[])
{
    // Setup Randomness
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

    return 0;
}
