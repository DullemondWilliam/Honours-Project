from subprocess import check_output, call
import matplotlib.pyplot as plt

import re
import csv

DATA_POINTS = 30


def callExe(filterSize, hashes, set1Size, set2Size, setDiff):
    cmd = ["C:\\Users\\William\\Documents\\Honours\\release\\Honours.exe",
           filterSize, hashes, set1Size, set2Size, setDiff]

    output = str(check_output(cmd))
    # print(call(cmd))
    # print(re.findall(r'\d+', output))
    return re.findall(r'\d+', output)


# def createTitle(filterSize, hashes, set1Size, set2Size, setDiff, measuring):
#     if type(filterSize) == list:
#         arr = filterSize
#     elif type(hashes) == list:
#         arr = hashes
#     elif type(set1Size) == list:
#         arr = set1Size
#     elif type(set2Size) == list:
#         arr = set2Size
#     elif type(setDiff) == list:
#         arr = setDiff
#     return ""


def createCSV(filterSize, hashes, set1Size, set2Size, setDiff, measuring):

    yLabel = "Time" if measuring == 2 else "Difference"
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
    elif type(set2Size) == list:
        arr = set2Size
        xLabel = "Set Two Size"
    elif type(setDiff) == list:
        arr = setDiff
        xLabel = "Difference Count"

    title = xLabel + str(arr) + " by " + yLabel

    writer = csv.writer(open("results//" + title + ".csv", 'w', newline='' ))
    writer.writerow(["", "Regular", "Method1", "Method2"])

    xAxis = []
    regAxis = []
    meth1 = []
    meth2 = []

    for i in list(range(int(arr[0]), int(arr[1]), round(abs(int(arr[0]) - int(arr[1])) / DATA_POINTS))):
        xAxis.append(i)
        result = callExe(str(i) if type(filterSize) == list else filterSize,
                         str(i) if type(hashes) == list else hashes,
                         str(i) if type(set1Size) == list else set1Size,
                         str(i) if type(set2Size) == list else set2Size,
                         str(i) if type(setDiff) == list else setDiff)

        info = [i, result[0 + measuring], result[3 + measuring], result[6 + measuring]]
        writer.writerow(info)

        regAxis.append(result[0 + measuring])
        meth1.append(result[3 + measuring])
        meth2.append(result[6 + measuring])

    plt.plot(xAxis, regAxis, label="regAxis")  # plotting the points
    plt.plot(xAxis, meth1, label="method 1")  # plotting the points
    plt.plot(xAxis, meth2, label="method 2")  # plotting the points

    plt.title(title)
    plt.xlabel(xLabel)  # naming the x axis
    plt.ylabel(yLabel)  # naming the y axis
    plt.legend()
    # plt.show()
    plt.savefig("results//" + title + ".png")
    plt.gcf().clear()

    # plt.close()
createCSV(["1000", "1000000"], "3", "1000", "1000", "600", 0)

createCSV("1000000", ["1", "32"], "10000", "1000", "100", 0)
createCSV("1000000", "3", "10000", ["1000", "100000"], ["100", "600"], 0)
createCSV("1000000", "3", "10000", "1000", ["100", "600"], 0)

