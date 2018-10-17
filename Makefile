CC=gcc
LINKER=gcc
INC_DIR=inc
INCLUDES=-I. -I$(INC_DIR)
CFLAGS=-I. -c -g -Wall $(INCLUDES)
LINKARGS=-lm -g
TARGET=out
BUILD_DIR=build
OUTPUT_DIR=bin
LIBS=-lm
SOURCE_DIR=src
LIB_DIR=$(SOURCE_DIR)/lib
SRCEXT=c
OBJEXT=o

SOURCES=$(shell find $(SOURCE_DIR) -type f -name *.c)
OBJECTS=$(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.c=.o))

OBJECT_FILES= test.o qdbmp.o

all : $(TARGET) includes

$(TARGET) : $(OBJECTS)
	$(LINKER) $(LINKARGS) -g $^ -o $(OUTPUT_DIR)/$@ $(LIBS) 

$(BUILD_DIR)/%.$(OBJEXT) : $(SOURCE_DIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	$(CC) $(CFLAGS) $(INC_DIR) -MM $(SOURCE_DIR)/$*.$(SRCEXT) > $(BUILD_DIR)/$*.$(DEPEXT)
	cp -f $(BUILD_DIR)/$*.$(DEPEXT) $(BUILD_DIR)/$*.$(DEPEXT).tmp
	sed -e 's|.*:|$(BUILD_DIR)/$*.$(OBJEXT):|' < $(BUILD_DIR)/$*.$(DEPEXT).tmp > $(BUILD_DIR)/$*.$(DEPEXT)
	sed -e 's/.*://' -e 's/\\$$//' < $(BUILD_DIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILD_DIR)/$*.$(DEPEXT)
	rm -f $(BUILD_DIR)/$*.$(DEPEXT).tmp
	
clean :
	rm -rf $(BUILD_DIR)

includes:
	if [ -d $(INC_DIR) ]; \
	then \
	rm -rf $(INC_DIR); \
	fi
	mkdir -p $(INC_DIR)
	find $(SOURCE_DIR) -name *.h -exec cp --parents \{\} $(INC_DIR) \;
	for DIR in $(shell ls -d $(INC_DIR)/*); \
	do \
	cp -r $$DIR/* $$DIR/..; \
	rm -rf $$DIR; \
	done
