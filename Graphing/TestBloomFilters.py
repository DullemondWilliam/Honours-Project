from subprocess import check_output, call
import matplotlib.pyplot as plt

import re
import csv

DATA_POINTS = 30


def callExe(filterSize, setSize):
    cmd = ["C:\\Users\\William\\Documents\\Honours\\Bloomfilter\\release\\Honours.exe",
           '-bt', str(filterSize), str(setSize), '-h']

    output = str(check_output(cmd))

    return output

print(callExe(10000, 1000))


# createCSV("1000000", ["1", "32"], "10000", "1000", "100", 0)
# createCSV("1000000", "3", "10000", ["1000", "100000"], ["100", "600"], 0)
# createCSV("1000000", "3", "10000", "1000", ["100", "600"], 0)

