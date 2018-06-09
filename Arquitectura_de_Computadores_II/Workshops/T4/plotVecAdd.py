
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D, get_test_data
from matplotlib import cm
import numpy as np

def main():
    data = open("outputVecAdd.txt").readlines()
    X = []
    Y = []
    Z = []
    Z2= []
    xLabel="Threads per Block"
    yLabel="Number of Iterations"
    zLabel="Time"
    for line in data:
        lineData = line.split(" ")
        if len(lineData) > 1 and lineData[0] == "Using":
            X.append(int(lineData[1]))
            Y.append(int(lineData[2]))
            Z.append(float(lineData[3]))
            Z2.append(float(lineData[4]))
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(X, Y, Z)
    ax.set_xlabel(xLabel)
    ax.set_ylabel(yLabel)
    ax.set_zlabel(zLabel)
    plt.show()

if __name__ == '__main__':
    main()
