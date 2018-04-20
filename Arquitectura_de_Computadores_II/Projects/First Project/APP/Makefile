# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11 `pkg-config --libs --cflags opencv`
 
# File names
EXEC = cipher
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS)  $(CC_FLAGS) -o $(EXEC)
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)