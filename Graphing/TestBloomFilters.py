from subprocess import check_output, call
import matplotlib.pyplot as plt
import numpy as np

import re
import csv

DATA_POINTS = 30


def callExe(filterSize, setSize):
    cmd = ["C:\\Users\\William\\Documents\\Honours\\Bloomfilter\\release\\Honours.exe",
           '-bt', str(filterSize), str(setSize), '-h']

    output = str(check_output(cmd))

    return float(re.findall(r'\d+', output)[0])

print(callExe(10000, 1000))

n = 0.0
lineA = np.array([0.0])
lineB = np.array([0.0])
lineC = np.array([0.0])
lineD = np.array([0.0])
lineE = np.array([0.0])
xAxis = np.array([0.0])
while 1:
    n = float(2 ** (len(lineE) + 12))
    print(n)
    if lineA[-1] < 50:
        lineA = np.append(lineA, (callExe(2000000, n)/n)*100)
    if lineB[-1] < 50:
        lineB = np.append(lineB, (callExe(4000000, n)/n)*100)
    if lineC[-1] < 50:
        lineC = np.append(lineC, (callExe(6000000, n)/n)*100)
    if lineD[-1] < 50:
        lineD = np.append(lineD, (callExe(8000000, n)/n)*100)
    if lineE[-1] < 50:
        lineE = np.append(lineE, (callExe(10000000, n)/n)*100)
        print(lineE[-1])
    else:
        break
    xAxis = np.append(xAxis, n)

    # print(lineA)
    # print(lineB)
    # print(lineC)
    # print(lineD)
    # print(lineE)

print(len(xAxis[0:len(lineA)]))
print(len(str(lineA)))

plt.plot(xAxis[:len(lineA)], lineA, label="2,000,000")  # plotting the points
plt.plot(xAxis[:len(lineB)], lineB, label="4,000,000")  # plotting the points
plt.plot(xAxis[:len(lineC)], lineC, label="6,000,000")  # plotting the points
plt.plot(xAxis[:len(lineD)], lineD, label="8,000,000")  # plotting the points
plt.plot(xAxis[:len(lineE)], lineE, label="19,000,000")  # plotting the points
plt.title("Bloom Filter Failure Rate")
plt.xlabel("Elements Added")  # naming the x axis
plt.ylabel("Percent of Overlapping Elements(%)")  # naming the y axis
plt.ylim(top=50)
plt.legend()

plt.minorticks_on()
plt.grid(which='major', linestyle='dashed', linewidth='0.5', color='black')  # Customize the major grid
plt.grid(which='minor', linestyle=':', linewidth='0.5', color='black', alpha=.5)  # Customize the minor grid

plt.show()



# createCSV("1000000", ["1", "32"], "10000", "1000", "100", 0)
# createCSV("1000000", "3", "10000", ["1000", "100000"], ["100", "600"], 0)
# createCSV("1000000", "3", "10000", "1000", ["100", "600"], 0)

