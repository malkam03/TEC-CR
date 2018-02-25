
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt

def main():
    data = sys.stdin.readlines()
    X = []
    Y = []
    for line in data:
        lineData = line.split(" ")
        if len(lineData) == 5:
            X.append(float(lineData[3]))
            Y.append(int(lineData[1]))
    plt.plot(X, Y, 'ro')
    plt.axis([0, max(X), 0, max(Y)])
    plt.ylabel("Steps")
    plt.xlabel("time(s)")
    plt.show()
    

if __name__ == '__main__':
    main()
