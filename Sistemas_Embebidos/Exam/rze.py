#!/usr/bin/env python3
# Hardware simulation of run-zero encoding
# Embedded System Final test
# Instituto Tecnológico de Costa Rica
# Author Malcolm Davis
from queue import Queue
import threading
import sys
ak = Queue()
bk = Queue()
ck = Queue()
dk = Queue()
fk = Queue()
ek = Queue()
remmind=1


def readInputMod():
    # Fill the pipe with the array passed to the script
    global remmind
    for arg in sys.argv[1:]:
        ak.put(int(arg))
    remmind = len(sys.argv) -1


def splitMod():
    # Split the input value into two for count and delay modules
    while(remmind>0):
        try:
            val =ak.get(block=True,timeout=1)
        except:
            break
        bk.put(val)
        ck.put(val)


def countMod():
    # Counts if the input is 0 else send the count
    counter = 0
    while(remmind>0):
        try:
            val = bk.get(block=True,timeout=1)
        except:
            break
        if (val==0):
            counter+=1
        else:
            dk.put(counter)
            counter=0


def delayMod():
    # Ignore 0 inputs and bypass the others
    while(remmind>0):
        try:
            val = ck.get(block=True,timeout=1)
        except:
            break
        if (val!=0):
            ek.put(val)


def joinMod():
    # Waits for the input of count and delayMod
    while(remmind>0):
        try:
            count = dk.get(block=True,timeout=1)
            delayed = ek.get(block=True,timeout=1)
        except:
            break
        fk.put(count)
        fk.put(delayed)


def printMod():
    # Prints the result
    global remmind
    while(remmind>0):
        count = fk.get()
        deleyed = fk.get()
        print(count)
        print(deleyed)
        remmind -= count+1


def main():
    readInputMod()
    threading.Thread(target=splitMod).start()
    threading.Thread(target=delayMod).start()
    threading.Thread(target=countMod).start()
    threading.Thread(target=printMod).start()
    threading.Thread(target=joinMod).start()


if __name__ ==  "__main__":
    main()
