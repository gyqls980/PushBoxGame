CC = g++
TARGET = test1main
SOURCES = test2.cpp

LDFLAGS = -lncurses	-std=c++11

all :
	$(CC)	-o	$(TARGET)	$(SOURCES)	$(LDFLAGS)

clean :
	rm	-rf	*.o	$(TARGET)
