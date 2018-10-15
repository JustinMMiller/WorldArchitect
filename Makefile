CC=gcc
LINKER=gcc
INCLUDES=-I.
CFLAGS=-I. -c -g -Wall $(INCLUDES)
LINKARGS=-lm -g
LIBS=-lm
TARGET=out
BUILD_DIR=build
OUTPUT_DIR=bin
LIB_DIR=lib
SOURCE_DIR=src

OBJECT_FILES= test.o qdbmp.o

$(TARGET) : $(addprefix $(BUILD_DIR)/, $(OBJECT_FILES))
	$(LINKER) $(LINKARGS) -g $^ -o $@ $(LIBS) 

test.o : $(SOURCE_DIR)/test.c
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@ 

qdbmp.o : $(LIB_DIR)/qdbmp/qdbmp.c
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@ 

clean :
	rm $(OBJECT_FILES)
