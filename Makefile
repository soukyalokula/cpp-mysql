#Soukya Lokula
#z1776873
#Assignment 3


CC=g++
CCFLAGS=-O -std=c++11

all: load query

load: load.o
	$(CC) $(CCFLAGS) -o load load.o -lpq
load.o: load.cc
	$(CC) $(CCFLAGS) -c load.cc
query: query.o
	$(CC) $(CCFLAGS) -o query query.o -lpq
query.o: query.cc
	$(CC) $(CCFLAGS) -c query.cc

clean:
	-rm *.o load query
