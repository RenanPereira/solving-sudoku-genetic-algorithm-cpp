#include <fstream>
#include <sstream>
#include "SudokuSkelleton.h"

using std::string;
using std::vector;


SudokuSkelleton::SudokuSkelleton(int sudoku_lenght, string file_name)
{   
    vector< vector<int> > file_input;

    //read file to vector of vectors
    std::ifstream cin(file_name);
    std::string line;
    while( std::getline(cin, line) ) 
    {	
    	vector<int> sudoku_lin = {};

        std::istringstream ss(line);
		while (ss >> line)
		{ 
			sudoku_lin.push_back( stoi(line) ); 
		}

        file_input.push_back( sudoku_lin );
    }

    //test if the size of the sudoku the equal to the sudoku lenght
    int aux = 1 + (file_input.size() - sudoku_lenght);
    if ( aux!=1 )
   	{ 	
   		printf("Problem in the sudoku file!\n");
    	abort(); 
    }
    for (int i = 0; i < int(file_input.size()); ++i)
    {	
    	aux = 1 + (file_input[i].size() - sudoku_lenght);
    	if ( aux!=1 )
    	{	
    		printf("Problem in the sudoku file!\n");
    		abort();
    	}
    }

    sudokuSkelleton = file_input;
}

void SudokuSkelleton::toString()
{
	for (int i = 0; i < int(sudokuSkelleton.size()); ++i)
    {
    	for (int j = 0; j < int(sudokuSkelleton[i].size()); ++j)
    	{	
    		printf("%i ", sudokuSkelleton[i][j]);
    	}
    	printf("\n");
    }
}

int SudokuSkelleton::numberOfClues()
{
	int clues = 0;
	for (int i = 0; i < int(sudokuSkelleton.size()); ++i)
	{	
		for (int j = 0; j < int(sudokuSkelleton[i].size()); ++j)
		{
			if ( sudokuSkelleton[i][j]!=0 ){ clues = clues + 1; }
		}
	}

	return clues;
}
