CC := g++
CFLAGS := -Wall -O3

SRCFILES := $(wildcard source/*.cpp)

all: 
	$(CC) $(CFLAGS) source/*.cpp -I./includes/ -I./extern/ -I/extern/qpOASES/ -I/usr/local/include/eigen3/ -lqpOASES -lpruio -o bin/main 

#obj/%.o: source/%.cpp
#	$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./extern -I/extern/qpOASES -I/usr/local/include/eigen3/ 


.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*

run:
		bin/main

