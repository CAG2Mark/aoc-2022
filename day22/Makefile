CC = clang++
CFLAGS = -g -std=c++17
CFLAGS += -O2
CFLAGS += -I../utils -fsanitize=address

.PHONY: all clean

r1: p1
	./p1

r2: p2
	./p2

all: p1 p2

p1: p1.o
	$(CC) -o p1 ../utils/aocutils.o $^ $(CFLAGS)

p2: p2.o
	$(CC) -o p2 ../utils/aocutils.o $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

json: clean
	bear -- make all -j2

clean:
	rm -f p1 p2 p1.o p2.o