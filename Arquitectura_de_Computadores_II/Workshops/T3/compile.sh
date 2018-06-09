#!/bin/bash
cd ./pi_neon
/opt/android-ndk-r16b/ndk-build
cd ../saxpy_neon
/opt/android-ndk-r16b/ndk-build
cd ../matMult_neon
/opt/android-ndk-r16b/ndk-build
