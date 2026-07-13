#ifndef SUDOKUANSATZ_H
#define SUDOKUANSATZ_H

#include <vector>
#include "SudokuSkelleton.h"

class SudokuAnsatz
{
private:
	std::vector< std::vector<int> > sudokuAnsatz;
    int sudokuWeight;

private:
	void setWeight(int weight){ sudokuWeight = weight; }
	
public:
	std::vector< std::vector<int> > loadByLines(SudokuSkelleton);
	SudokuAnsatz(std::vector< std::vector<int> >);
	SudokuAnsatz(SudokuSkelleton);
	void toString();
	int linesOBS();
	int columnsOBS();
	int blocksOBS();
	int lineWeight(int );
	int columnWeight(int );
	int blockWeight(int , int );
	int calculateWeight();
	int getWeight(){ return sudokuWeight; }
	std::vector< std::vector<int> > getAnsatz(){ return sudokuAnsatz; }
};

#endif