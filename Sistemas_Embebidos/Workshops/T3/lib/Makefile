# Declaration of variables
CC = gcc
AR = ar
LD = ld
RANLIB = ranlib
AR_FLAGS = rv
CC_FLAGS = -w
INCLUDE_PATH = ../include

# File Names
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
ARCHIVES = $(OBJECTS:.o=.a)
SO_FILES = $(ARCHIVES:.a=.so)

# Main Target
all: static dynamic

# Static Libraries build
static: $(OBJECTS)
		$(AR) $(AR_FLAGS) $(ARCHIVES) $(OBJECTS)
		$(RANLIB) $(ARCHIVES) 

# Dynamic Libraries build
dynamic: $(OBJECTS)
		$(LD) -o $(SO_FILES) $(OBJECTS) -shared

# To obtain object files
%.o: %.c
		$(CC) -c $(CC_FLAGS) $< -o $@ -I$(INCLUDE_PATH)

# To remove generated files
clean:
	rm *.o *.a *.so
