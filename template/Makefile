CC = g++
CFLAGS = -g -std=c++11 
CFLAGS += -O2

.PHONY: all clean

r1: p1
	./p1

r2: p2
	./p2

p1:
	$(CC) -o p1 p1.cpp $(CFLAGS)

p2:
	$(CC) -o p2 p2.cpp $(CFLAGS)

json: clean
	bear -- make main

clean:
	rm -f p1 p2