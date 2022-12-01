CC = g++
CFLAGS = -g -std=c++11 
CFLAGS += -O2

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean

run: main
	./main

main: $(OBJ)
	mkdir -p ./$(BIN)
	$(CC) -o main $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

json: clean
	bear -- make main

clean:
	rm -rf $(BIN) $(OBJ) $(DEP)