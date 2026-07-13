SHELL := /bin/bash
CXX = g++ -O3 -Wall -Wextra -Wfloat-equal -Wundef -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -std=c++11 -fopenmp

INCLUDE_DIRS = -Isrc

DEPS = src/sudoku.h \
	   src/command_line_args_processor.h \
	   src/SudokuSkelleton.h \
	   src/SudokuAnsatz.h

OBJ = obj/main.o \
	  obj/command_line_args_processor.o \
	  obj/sudoku.o \
	  obj/SudokuSkelleton.o \
	  obj/SudokuAnsatz.o

obj/%.o: src/%.cpp $(DEPS)
	$(CXX) $(INCLUDE_DIRS) -c $< -o $@

run: $(OBJ) 
	$(CXX) $(OBJ) $(INCLUDE_DIRS) -o bin/sudoku.out

clean: 
	rm -f bin/sudoku.out $(OBJ)
