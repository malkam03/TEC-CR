SUMMARY = "Linux module for BCM2835 timer"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"
inherit module
SRC_URI = "file://Makefile \
            file://timer.c \
            file://COPYING \
            file://random.c \
            file:main.c    \
          "
S = "${WORKDIR}"
# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
