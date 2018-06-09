TARGET = FPGAHPS
#
CROSS_COMPILE = arm-linux-gnueabihf-


ALT_DEVICE_FAMILY ?= soc_cv_av


CFLAGS = -g -Wall -I media/root/40077ce6-e4b3-4238-bc9b-bf6a59161e96/altera-cyclone-v/hwlib/include -D$(ALT_DEVICE_FAMILY) -std=c++11 `pkg-config --libs --cflags opencv`



LDFLAGS = -g -Wall -std=c++11 `pkg-config --libs --cflags opencv`
CC = $(CROSS_COMPILE)g++
ARCH= arm


build: $(TARGET)


$(TARGET): cipher.o
	$(CC) $(LDFLAGS) $^ -o $@


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *~ 