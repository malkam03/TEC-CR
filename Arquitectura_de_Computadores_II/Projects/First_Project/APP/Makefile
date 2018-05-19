# Declaration of variables
CC = g++
CC_FLAGS = -std=c++0x  `pkg-config --libs --cflags opencv`  

# Main Target
all: cipher


# Image Cipher 
cipher: cipher.cpp
	$(CC) cipher.cpp  $(CC_FLAGS) -o cipher

 
# To remove generated files
clean:
	rm -f cipher *.o 