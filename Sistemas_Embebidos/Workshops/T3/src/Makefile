# Declaration of variables
CC = gcc
CC_FLAGS = -w
INCLUDE_PATH = ../include
LIB_PATH = ../lib
BIN_PATH = ../bin
STATIC_EXEC = calculadora_c
DYNAMIC_EXEC = calculadora_d
LIBS = -lse_math -lm

# File Names
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Main Target
all: static dynamic

# Static Libraries build
static:
		$(CC) $(SOURCES) $(STATIC_LIBS) -L. $(LIBS) -L$(LIB_PATH) -o $(BIN_PATH)/$(STATIC_EXEC) -I$(INCLUDE_PATH)

# Dynamic Libraries build
dynamic:
		$(CC) -o $(BIN_PATH)/$(DYNAMIC_EXEC) $(SOURCES) -I$(INCLUDE_PATH) -L$(LIB_PATH) $(LIBS)

# To obtain object files
%.o: %.c
		$(CC) -c $(CC_FLAGS) $< -o $@ -I$(INCLUDE_PATH)

# To remove generated files
clean:
	rm $(BIN_PATH)/*
