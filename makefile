CC=g++ -std=c++11 -c
CFLAGS=-I./lib/ -ggdb3

BIN_FOLDER=./bin/
SRC_FOLDER=./src/

SRC=$(wildcard $(SRC_FOLDER)*.cpp)
OBJ=$(addprefix $(BIN_FOLDER),$(notdir $(SRC:.cpp=.o)))
EXE=./bin/main

all: $(OBJ)
	g++ -o $(EXE) $(OBJ)

./bin/%.o: ./src/%.cpp
	@mkdir -p $(BIN_FOLDER)
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(BIN_FOLDER)*.o
