CC=gcc
LINKER=gcc
INCLUDES=-I.
CFLAGS=-I. -c -g -Wall $(INCLUDES)
LINKARGS=-lm -g
LIBS=-lm
TARGET=out

OBJECT_FILES= test.o qdbmp.o

$(TARGET) : $(OBJECT_FILES)
	$(LINKER) $(LINKARGS) -g $^ -o $@ $(LIBS) 
	make clean

test.o : test.c
	$(CC) $(CFLAGS) $< -o $@ 

qdbmp.o : qdbmp.c
	$(CC) $(CFLAGS) $< -o $@ 

clean :
	rm $(OBJECT_FILES)
