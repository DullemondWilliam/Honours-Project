from subprocess import check_output, call
import matplotlib.pyplot as plt

import re
import csv

DATA_POINTS = 20


def callBloomFilter(filterSize, hashes, set1Size, set2Diff, setDiff):
    cmd = ["C:\\Users\\William\\Documents\\Honours\\Bloomfilter\\release\\Honours.exe", '-b',
           filterSize, set1Size, str(int(set1Size) + int(set2Diff)), setDiff, hashes]

    output = str(check_output(cmd).decode('UTF-8'))
    print(output)
    # print(re.findall(r'\d+', output))
    return re.findall(r'\d+', output)


def createCSV(filterSize, hashes, set1Size, set2SizeDiff, setDiff, measuring):
    # Determine Graph Labels and Title
    yLabel = "Time" if measuring == 1 else "deviation from Difference"
    xLabel = ""
    arr = []
    if type(filterSize) == list:
        arr = filterSize
        xLabel = "Filter Size"
    elif type(hashes) == list:
        arr = hashes
        xLabel = "Hashes"
    elif type(set1Size) == list:
        arr = set1Size
        xLabel = "Set One Size"
    elif type(set2SizeDiff) == list:
        arr = set2SizeDiff
        xLabel = "Set Two Size"
    elif type(setDiff) == list:
        arr = setDiff
        xLabel = "Difference Count"
    title = xLabel + str(arr) + " by " + yLabel

    # Start CSV and write first line
    writer = csv.writer(open("results//" + title + ".csv", 'w', newline='' ))
    writer.writerow(["", "Regular", "Method1", "Method2"])

    # Define Vectors to store information
    xAxis = []
    regAxis = []
    meth1 = []
    meth2 = []

    # The Main Loop Iterate through the designated variable
    for i in list(range(int(arr[0]), int(arr[1]), round(abs(int(arr[0]) - int(arr[1])) / DATA_POINTS))):
        xAxis.append(i)
        # Call BloomFilter Function and save result
        result = callBloomFilter(str(i) if type(filterSize) == list else filterSize,
                                 str(i) if type(hashes) == list else hashes,
                                 str(i) if type(set1Size) == list else set1Size,
                                 str(i) if type(set2SizeDiff) == list else set2SizeDiff,
                                 str(i) if type(setDiff) == list else setDiff)

        # print(result)
        info = [i, result[0 + measuring], result[2 + measuring], result[4 + measuring]]
        writer.writerow(info)

        regAxis.append(result[0 + measuring] if measuring else 0)
        meth1.append(result[2 + measuring] if measuring else int(result[0]) - int(result[2]))
        meth2.append(result[4 + measuring] if measuring else int(result[0]) - int(result[4]))

    plt.plot(xAxis, regAxis, label="regAxis")  # plotting the points
    plt.plot(xAxis, meth1, label="method 1")  # plotting the points
    plt.plot(xAxis, meth2, label="method 2")  # plotting the points

    plt.title(title)
    plt.xlabel(xLabel)  # naming the x axis
    plt.ylabel(yLabel)  # naming the y axis
    plt.legend()

    plt.show()
    plt.savefig("results//" + title + ".png")
    plt.gcf().clear()

    # plt.close()
# createCSV(["1000", "1000000"], "3", "1000", "1000", "600", 0)

# createCSV("1000000", ["1", "32"], "10000", "1000", "100", 0)
# createCSV("100000", "-h", "10000", "10000", ["100", "10000"], 0)
createCSV("100000", "3", ["1000", "10000"], "0", "1000", 0)


# createCSV(filterSize, hashes, set1Size, set2diff, setDiff, measuring):

