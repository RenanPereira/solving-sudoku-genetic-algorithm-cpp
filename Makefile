SHELL := /bin/bash
CXX = g++ -std=c++11 -fopenmp
#CXX = g++ -Wall -Wextra -Wfloat-equal -Wundef -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -std=c++11 -fopenmp

DEPS = src/parameters.h src/sudoku.h
OBJ = obj/main.o obj/sudoku.o


obj/%.o: src/%.cpp $(DEPS)
	$(CXX) -I/usr/local/include -c $< -o $@

run: $(OBJ) 
	$(CXX) -o bin/sudoku.out $(OBJ) -L/usr/local/lib -lm

clean: 
	rm -f bin/sudoku.out $(OBJ)

