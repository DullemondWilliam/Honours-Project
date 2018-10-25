#include <QCoreApplication>
#include "CountBloomFilter.h"
#include "Bloomfilter.h"
#include "MurmurHash3.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include "SetDifference.h"
#include <time.h>

using namespace std;

void generateSets( QList<QString>& set1, QList<QString>& set2);

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    //Usage
    // ./Honours FilterSize HashSize set1Size set2Size set1Diff

    srand(time(nullptr));

    int filterSize = 10000000;
    int hashSize = 10;
    int set1Size = 40000;
    int set2Size = 20000;
    int set1Diff = 700;

    if(argc > 1)
    {
        filterSize = stoi(argv[1]);
        hashSize = stoi(argv[2]);
        set1Size = stoi(argv[3]);
        set2Size = stoi(argv[4]);
        set1Diff = stoi(argv[5]);

    }

    QList<QString> set1;
    QList<QString> set2;
    BloomFilter bf1 = BloomFilter(filterSize, hashSize);
    BloomFilter bf2 = BloomFilter(filterSize, hashSize);

    for(int i=0; i<max(set1Size,set2Size); ++i)
    {
        QString a = i < set1Diff ? QString::number(i)+"a" : QString::number(i);
        QString b = i < set1Diff ? QString::number(i)+"b" : QString::number(i);

        if(i < set1Size)
        {
            set1.append(a);
            bf1.addElement(a);
        }
        if(i < set2Size)
        {
            set2.append(b);
            bf2.addElement(b);
        }
    }

    SetDifference::Answer ans1 = SetDifference::setDifference(set1, set2);
    SetDifference::Answer ans2 = SetDifference::methodOne(bf1, bf2);
    SetDifference::Answer ans3 = SetDifference::methodTwo(set1, bf2);

    cout << "Real Set    One: " << ans1.set1 << "\t Set Two: " << ans1.set2 << "\tTime: " << ans1.time << endl;
    cout << "TestOne Set One: " << ans2.set1 << "\t Set Two: " << ans2.set2 << "\tTime: " << ans2.time << endl;
    cout << "TestTwo Set One: " << ans3.set1 << "\t Set Two: " << ans3.set2 << "\tTime: " << ans3.time << endl;

    return 0;
    // a.exec();
}
