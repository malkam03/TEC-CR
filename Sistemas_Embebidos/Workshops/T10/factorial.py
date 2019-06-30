#!/usr/bin/env python3
# Hardware simulation of factorial
# Author Malcolm Davis
from queue import Queue
import threading
import sys
ck = Queue()
ak = Queue()
fk = Queue()
bk = Queue()
dk = Queue()
ek = Queue()
cont = True
if(len(sys.argv)>1):
    max = int(sys.argv[1])
else:
    max = 100000000

def multMod():
    while(cont):
        val = ck.get(True)*fk.get(True)
        ak.put(val)


def splitMod():
    while(cont):
        val =bk.get(True)
        ek.put(val)
        ck.put(val)
        dk.put(val)


def delay1Mod():
    first = True
    while(cont):
        if first:
            bk.put(1)
            first=not first
        else:
            bk.put(ak.get())


def countMod():
    count = 1
    while(cont):
        fk.put(count)
        count+=1
        ek.get()


def printMod():
    global cont
    while (cont):
        val = dk.get()
        if (val>max):
            cont = not cont
            break
        print(val)


def main():
    threading.Thread(target=multMod).start()
    threading.Thread(target=splitMod).start()
    threading.Thread(target=delay1Mod).start()
    threading.Thread(target=countMod).start()
    threading.Thread(target=printMod).start()


if __name__ ==  "__main__":
    main()