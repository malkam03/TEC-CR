# Declaration of variables
CC = g++
CC_FLAGS = -w -lboost_iostreams -lboost_system -lboost_filesystem  -L/usr/lib/ -lboost_program_options

# File names
EXEC = run
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(CC_FLAGS)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
