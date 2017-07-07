SRC=./src/file_functions.cpp ./src/review.cpp ./src/word.cpp ./src/main.cpp ./src/hash_table_inst.cpp
OBJ=./bin/main.o ./bin/file_functions.o ./bin/review.o ./bin/word.o ./bin/hash_table_inst.o
EXE=./bin/main

all: $(OBJ)
	@mkdir -p bin
	gcc -o $(EXE) $(OBJ)

$(OBJ): $(SRC)
	@mkdir -p bin
	gcc -c -o $@ $< --std=c++11
