LIB=include/Libgpio.h
LIBD=build/Libgpio.so
OBJ=Libgpio.o

$(LIBD): $(OBJ)
	$(LD) $(LFLAGS) $(LIBD) $(OBJ)
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./build

$(OBJ): $(CCG)
	$(CC)  $(CFLAGS) $(LSRC)

$(CCG):
	 . $(CCG)

clean:
	rm -f  $(OBJ) $(LIBD)