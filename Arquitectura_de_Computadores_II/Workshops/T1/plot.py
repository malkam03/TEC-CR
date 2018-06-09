
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt

def main():
    data = sys.stdin.readlines()
    X = []
    Y = []
    xLabel=""
    yLabel=""
    for line in data:
        lineData = line.split(" ")
        if len(lineData) == 5:
            X.append(float(lineData[3]))
            Y.append(int(lineData[1]))
            if xLabel == "":
                yLabel = lineData[0]
                xLabel = lineData[2]
    plt.plot(X, Y, 'ro')
    plt.axis([0, max(X), 0, max(Y)])
    plt.ylabel(yLabel)
    plt.xlabel(xLabel)
    plt.show()
    

if __name__ == '__main__':
    main()
