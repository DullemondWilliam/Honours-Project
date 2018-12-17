from subprocess import check_output, call
import matplotlib.pyplot as plt

import re
import csv
import time
from math import ceil

DATA_POINTS = 50


def callBloomFilter(filterSize, hashes, set1Size, set2Diff, setDiff):
    cmd = ["C:\\Users\\William\\Documents\\Honours\\Bloomfilter\\release\\Honours.exe", '-b',
           filterSize, set1Size, str(int(set1Size) + int(set2Diff)), setDiff, hashes]
    print("\t  " + check_output(cmd).decode('UTF-8'))
    return re.findall(r'\d+', str(check_output(cmd).decode('UTF-8')))


def createCSV(filterSize, hashes, set1Size, set2SizeDiff, setDiff, measuring):
    # Determine Graph Labels and Title
    yLabel = "Time (ms)" if measuring == 1 else "Error Percent (%)"
    xLabel = ""
    arr = []
    if type(filterSize) == list:
        arr = filterSize
        xLabel = "Filter Size"
    elif type(hashes) == list:
        arr = hashes
        xLabel = "# of Hashes"
    elif type(set1Size) == list:
        arr = set1Size
        xLabel = "Set Size"
    elif type(set2SizeDiff) == list:
        arr = set2SizeDiff
        xLabel = "Set Size Diff"
    elif type(setDiff) == list:
        arr = setDiff
        xLabel = "Size of Difference"
    title = xLabel + str(arr) + " by " + yLabel
    print(title)
    # Start CSV and write first line
    writer = csv.writer(open("results//" + title + ".csv", 'w', newline='' ))
    writer.writerow(["", "Regular", "Method1", "Method2"])

    # Define Vectors to store information
    xAxis = []
    regAxis = []
    meth1 = []
    meth2 = []

    # The Main Loop Iterate through the designated variable
    for i in list(range(int(arr[0]), int(arr[1]), ceil(abs(int(arr[0]) - int(arr[1])) / DATA_POINTS))):
        xAxis.append(i)
        # Call BloomFilter Function and save result
        result = callBloomFilter(str(i) if type(filterSize) == list else filterSize,
                                 str(i) if type(hashes) == list else hashes,
                                 str(i) if type(set1Size) == list else set1Size,
                                 str(i) if type(set2SizeDiff) == list else set2SizeDiff,
                                 str(i) if type(setDiff) == list else setDiff)

        info = [i, result[0 + measuring], result[2 + measuring], result[4 + measuring]]
        writer.writerow(info)

        regAxis.append(0)
        meth1.append(result[2 + measuring] if measuring else (1-(float(result[2])/float(i if type(setDiff) == list else result[measuring]))) * 100)
        meth2.append(result[4 + measuring] if measuring else (1-(float(result[4])/float(i if type(setDiff) == list else result[measuring]))) * 100)

    fig, ax = plt.subplots()

    plt.plot(xAxis, regAxis, label="regAxis")  # plotting the points
    plt.plot(xAxis, meth1, label="method 1")  # plotting the points
    plt.plot(xAxis, meth2, label="method 2")  # plotting the points

    desc = ("" if type(filterSize) == list else "M: " + filterSize + "\n") + \
           ("" if type(hashes) == list else "H: " + ("optimal" if hashes == '-h' else hashes) + "\n") + \
           ("" if type(set1Size) == list or type(set2SizeDiff) == list else
            "|A|: " + set1Size + "\n" + "|B|: " + str(int(set1Size) - int(set2SizeDiff)) + "\n") + \
           ("" if type(setDiff) == list else "|C|: " + setDiff + "\n")
    desc = desc[:-1]

    plt.title(title)
    plt.xlabel(xLabel)  # naming the x axis
    plt.ylabel(yLabel)  # naming the y axis
    plt.legend()

    props = dict(boxstyle='round', facecolor='white', alpha=0.75)
    plt.text(0.30, 0.98, desc, transform=ax.transAxes, fontsize=10, verticalalignment='top', bbox=props)

    plt.minorticks_on()
    plt.grid(which='major', linestyle='dashed', linewidth='0.5', color='black')  # Customize the major grid
    plt.grid(which='minor', linestyle=':', linewidth='0.5', color='black', alpha=.5)  # Customize the minor grid

    # plt.show()
    plt.savefig("results//" + title + ".png")
    plt.gcf().clear()
    fig.clear()
    ax.clear()
    plt.close()

# # # Accuracy over increase in Difference
# createCSV("100000", "-h", "10000", 0, ["1", "10000"], 0)
# #
# # # Accuracy over increase in Number of Hashes
# createCSV("100000", ["1", "20"], "10000", "0", "1000", 0)
# createCSV("100000", ["1", "110"], "10000", "0", "1000", 0)
# #
# # # Accuracy over increase in Filter Size(M)
# createCSV(["1000", "100000"], "-h", "10000", "0", "1000", 0)
# createCSV(["1000", "10000"], "-h", "10000", "0", "1000", 0)
# #
# # # Time over increase in Hashes (K)
# createCSV("100000", ["1", "500"], "10000", "0", "1000", 1)
# #
# # # Time over increase in Filter Size(M)
# createCSV(["10000", "1000000"], "-h", "100000", "0", "10000", 1)
# #
# # # Time over increase in |A| and |B|
# createCSV("100000", "-h", ["1000", "1000000"], "0", "1000", 1)

createCSV("100000", "-h", "10000", 0, ["1", "10000"], 0)

#####################################################
# # # Accuracy over increase in |A| and |B|
# createCSV("100000", "-h", ["100", "10000"], "0", "100", 0)
