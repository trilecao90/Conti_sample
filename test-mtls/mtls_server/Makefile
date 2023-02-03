FOLDER_NAME := $(shell basename $(CURDIR))
TARGET := $(FOLDER_NAME)

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
DEPENDS := $(SOURCES:.cpp=.d)

.PHONY :  all clean distclean

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $^ -o $@

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean distclean :
	rm -rf $(TARGET)
	rm -rf $(OBJECTS)
	rm -rf $(DEPENDS)
