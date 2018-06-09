# Declaration of variables
CC = gcc
CC_FLAGS = -pthread
 
# File names
EXEC = run
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS)  $(CC_FLAGS) -o $(EXEC)
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)