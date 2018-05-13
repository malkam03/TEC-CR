#!/bin/bash
adb push pi_neon/libs/armeabi-v7a/pi_par /data/local/tmp
adb shell /data/local/tmp/pi_par
adb push saxpy_neon/libs/armeabi-v7a/saxpy_neon /data/local/tmp
adb shell /data/local/tmp/saxpy_neon
adb push matMult_neon/libs/armeabi-v7a/matMult_neon /data/local/tmp
adb shell /data/local/tmp/matMult_neon