CC = g++
CFLAGS = -g
CFLAGS += -O2

.PHONY: all clean

r1: p1
	./p1

r2: p2
	./p2

p1: p1.o
	$(CC) -o p1 $^ $(CFLAGS)

p2: p2.o
	$(CC) -o p2 $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

json: clean
	bear -- make main

clean:
	rm -f p1 p2