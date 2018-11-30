#include "Controller.h"
#include <QCoreApplication>
#include "Bloomfilter.h"
#include "MurmurHash3.h"
#include <stdlib.h>     /* srand, rand */
#include "SetDifference.h"
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

// optimialNumberOfHashes   (m/n) ln 2
int Controller::optHashes(int expectedSetSize, int filterSize)
{
    return int(ceil(double(filterSize)/double(expectedSetSize) * double(.69314718056)));
}

//Regular Tests for Set Membership Accuracy Bloomfilter
// -b filterSize SetSize hashes
void Controller::testBloomFilter(int argc, char *argv[])
{
    if(argc < 4)
    {
        cout << "Give me some varibles you wanker" << endl;
        return;
    }

    int filterSize = stoi(argv[2]);
    int setSize = stoi(argv[3]);
    int hashSize = 1;
    if(!strcmp( argv[4],"-h"))
        hashSize = Controller::optHashes(setSize, filterSize);
    else
        hashSize = stoi(argv[6]);

    BloomFilter bf = BloomFilter(filterSize, hashSize);

    int bad = 0;
    for(int i=0; i < setSize; ++i)
    {
        if(bf.addElement(QString::number(i)))
            bad++;
        else
            bf.addElement(QString::number(i));
    }
    cout << "Overlaping Elements: " << bad << endl;
}

//Regular Tests for Set Membership Accuracy Count Bloomfilter
void Controller::testCountBloomFilter(int argc, char *argv[])
{
    cout << "test Count Bloom" << endl;
}

//Test For Set Difference Accuracy Bloomfilter
// -b filterSize Set1 Set2 difference hashes
void Controller::testCommBloomFilter(int argc, char *argv[])
{
    ///////////////////////////////////////////////////////////////////////////
    // ./honours -b filterSize set1Size set2Size hashSize
    // Collect User
    if(argc < 6)
    {
        cout << "Give me some varibles you wanker" << endl;
        return;
    }
    int filterSize = stoi(argv[2]);
    int set1Size = stoi(argv[3]);
    int set2Size = stoi(argv[4]);
    int set1Diff = stoi(argv[5]);
    int hashSize = strcmp(argv[6],"-h") ? stoi(argv[6]) :
        Controller::optHashes(max(set1Size, set2Size), filterSize);

//    cout << "Filter Size: " << filterSize << " Set1: " << set1Size << " Set2: "
//         << set2Size << " SetDiff: " << set1Diff << " Hashes: " << hashSize << endl;

    ///////////////////////////////////////////////////////////////////////////
    // Define variables and fill sets and BloomFilters
    QList<QString> set1;
    QList<QString> set2;
    BloomFilter bf1 = BloomFilter(filterSize, hashSize);
    BloomFilter bf2 = BloomFilter(filterSize, hashSize);

    for(int i=0; i<max(set1Size,set2Size); ++i)
    {
        if(i < set1Size)
        {
            QString a = QString::fromStdString(i < set1Diff ? to_string(i)+"a" : to_string(i));
            set1.append(a);
            bf1.addElement(a);
        }
        if(i < set2Size)
        {
            QString b = QString::fromStdString(i < set1Diff ? to_string(i)+"b" : to_string(i));
            set2.append(b);
            bf2.addElement(b);
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    // Find Differences through each method and Print

    SetDifference::Answer ans1 = SetDifference::setDifference(set1, set2);
    SetDifference::Answer ans2 = SetDifference::methodOne(bf1, bf2);
    SetDifference::Answer ans3 = SetDifference::methodTwo(set1, bf2);

    cout << "Real Diff: " << ans1.set1 << "\tTime: " << ans1.time << endl;
    cout << "Method One Diff: " << ans2.set1 << "\tTime: " << ans2.time << endl;
    cout << "Method Two Diff: " << ans3.set1 << "\tTime: " << ans3.time << endl;

}

//Test For  Set Difference Accuracy Count Bloomfilter
void Controller::testCommCountBloomFilter(int argc, char *argv[])
{
    cout << "test Comm Count Bloom" << endl;
}
