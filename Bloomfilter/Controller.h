#ifndef CONTROLLER_H
#define CONTROLLER_H


class Controller
{
    public:
        static int optHashes(int expectedSetSize, int filterSize);

        //Regular Tests for Set Membership Accuracy
        static void testBloomFilter(int argc, char *argv[]);
        static void testCountBloomFilter(int argc, char *argv[]);

        //Test For Set Difference Accuracy
        static void testCommBloomFilter(int argc, char *argv[]);
        static void testCommCountBloomFilter(int argc, char *argv[]);


};

#endif // CONTROLLER_H
