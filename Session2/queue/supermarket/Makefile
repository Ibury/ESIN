CC=gcc
CXX=g++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)A

CPPFLAGS=-Wall -ansi -std=c++11

PROGRAM=main

SRCS=$(PROGRAM).cpp queue.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

$(info $$OBJS is [${OBJS}])

DIRS=build

$(shell mkdir -p $(DIRS))

all: $(PROGRAM).e

$(PROGRAM).e: $(OBJS)
	$(CXX) -o build/$(PROGRAM).e build/$(OBJS)

$(PROGRAM).o: 
	$(CXX) -Wall -g -c $(PROGRAM).cpp -o build/$(PROGRAM).o

clean:
	$(RM) build/$(OBJS)

distclean: clean
	$(RM) build/$(PROGRAM).e
