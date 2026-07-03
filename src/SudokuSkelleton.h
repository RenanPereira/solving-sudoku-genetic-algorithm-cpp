#ifndef SUDOKUSKELLETON_H
#define SUDOKUSKELLETON_H

#include <string>
#include <vector>

class SudokuSkelleton
{
private: 
	std::vector< std::vector<int> > sudokuSkelleton;

public: 
	SudokuSkelleton(int , std::string );
	void toString();
	int numberOfClues();
	std::vector< std::vector<int> > getSkelleton(){ return sudokuSkelleton; }
};

#endif