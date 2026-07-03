#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <omp.h>
#include <algorithm>
#include "SudokuAnsatz.h"

using std::string;
using std::vector;
using std::tuple;


void SudokuAnsatz::toString()
{
	for (int i = 0; i < int(sudokuAnsatz.size()); ++i)
    {
    	for (int j = 0; j < int(sudokuAnsatz[i].size()); ++j)
    	{	
    		printf("%i ", sudokuAnsatz[i][j]);
    	}
    	printf("\n");
    }
}

int SudokuAnsatz::lineWeight(int line)
{	
	vector<int> sudoku_lin = sudokuAnsatz[line];

	int weight = 0;
	int sum_count = 0;
	for (int i = 0; i < int(sudoku_lin.size()); ++i)
	{
		int aux = count(sudoku_lin.begin(), sudoku_lin.end(), i+1);
		weight = weight + pow(aux-1,2);
		sum_count = sum_count + aux;
	}

	if ( sum_count!=int(sudokuAnsatz.size()) )
	{ 
		printf("Problem in lineWeight! Counting not equal to sudoku lenght!\n"); 
		abort(); 
	}

	return weight;
}

int SudokuAnsatz::columnWeight(int column)
{	
	vector<int> sudoku_col(sudokuAnsatz.size(),0);
	for (int i = 0; i < int(sudokuAnsatz.size()); ++i)
	{
		sudoku_col[i] = sudokuAnsatz[i][column];
	}

	int weight = 0;
	int sum_count = 0;
	for (int i = 0; i < int(sudoku_col.size()); ++i)
	{
		int aux = count(sudoku_col.begin(), sudoku_col.end(), i+1);
		weight = weight + pow(aux-1,2);
		sum_count = sum_count + aux;
	}

	if ( sum_count!=int(sudokuAnsatz.size()) )
	{ 
		printf("Problem in columnWeight! Counting not equal to sudokuAnsatz lenght!\n"); 
		abort(); 
	}

	return weight;
}

int SudokuAnsatz::blockWeight(int block_line, int block_column)
{	
	//Lenght of block: square root of the sudoku size, by definition
	int minor_square_size = int( sqrt( sudokuAnsatz.size() ) );

	if ( block_line<0 || block_line>minor_square_size )
	{ 
		printf("Sudoku block line out of bounds!\n"); 
		abort(); 
	}
	if ( block_column<0 || block_column>minor_square_size )
	{ 
		printf("Sudoku block column out of bounds!\n"); 
		abort(); 
	}

	int X = block_line*minor_square_size;
	int Y = block_column*minor_square_size;

	vector<int> sudoku_block(sudokuAnsatz.size(),0);
	int aux = 0;
	for (int i = X; i < X+minor_square_size; ++i)
	{
		for (int j = Y; j < Y+minor_square_size; ++j)
		{	
			sudoku_block[aux] = sudokuAnsatz[i][j];
			aux = aux + 1;
		}
	}

	int weight = 0;
	int sum_count = 0;
	for (int i = 0; i < int(sudoku_block.size()); ++i)
	{
		int current_index_counting = count(sudoku_block.begin(), sudoku_block.end(), i+1);
		weight = weight + pow(current_index_counting-1,2);
		sum_count = sum_count + current_index_counting;
	}

	if ( sum_count!=int(sudokuAnsatz.size()) )
	{ 
		printf("Problem in blockWeight! Counting not equal to sudoku lenght!\n"); 
		abort(); 
	}

	return weight;
}

int SudokuAnsatz::linesOBS()
{
	int obs = 0;
	for (int i = 0; i < int(sudokuAnsatz.size()); ++i)
	{ 
		obs = obs + lineWeight(i); 
	}
	
	return obs;
}

int SudokuAnsatz::columnsOBS()
{
	int obs = 0;
	for (int i = 0; i < int(sudokuAnsatz.size()); ++i)
	{ 
		obs = obs + columnWeight(i); 
	}

	return obs;
}

int SudokuAnsatz::blocksOBS()
{	
	int minor_square_size = int( sqrt(sudokuAnsatz.size()) );
	int obs = 0;

	for (int L = 0; L < minor_square_size; ++L)
	{	
		for (int C = 0; C < minor_square_size; ++C)
		{ 
			obs = obs + blockWeight(L, C); 
		}
	}

	return obs;
}

int SudokuAnsatz::calculateWeight()
{
	int W = 0;
	W = W + columnsOBS();
	W = W + blocksOBS();

	return W;
}


vector< vector<int> > SudokuAnsatz::loadByLines(SudokuSkelleton sudokuSkelletonAux)
{   
	vector< vector<int> > sudoku = sudokuSkelletonAux.getSkelleton();

    for (int i = 0; i < int(sudoku.size()); ++i)
    {	
    	vector<int> guesses = {};

    	//copy clues of the i-sudoku line to a vector
    	vector<int> line_elements = {};
    	for (int j = 0; j < int(sudoku[i].size()); ++j)
    	{	
    		if ( sudoku[i][j]!=0 )
    		{
    			line_elements.push_back( sudoku[i][j] );
    		}
    	}

    	//create vector with guesses: it contains number 1-Nsudoku, excluding clues
    	for (int j = 0; j < int(sudoku[i].size()); ++j)
    	{	
    		int element = j+1;
    		bool add_element = true;
    		for (int k = 0; k < int(line_elements.size()); ++k)
    		{
    			if ( line_elements[k]==element )
    			{
    				add_element = false;
    			}
    		}
    		if (add_element==true){ guesses.push_back( element ); }
    	}
		
		//using a pseudo random number generator, randomly fill sudoku skeleton with guesses
    	for (int j = 0; j < int(sudoku[i].size()); ++j)
    	{
    		if ( sudoku[i][j]==0 )
    		{	
    			int pos = 0;
    			if ( guesses.size()>1 )
				{ 
					pos = ( rand() % guesses.size() ); 
				}
    			sudoku[i][j] = guesses[pos];
    			guesses.erase( guesses.begin()+pos );
    		}
    	}
    } 

	return sudoku;
}

SudokuAnsatz::SudokuAnsatz(vector< vector<int> > sudokuAnsatzAux)
{
	sudokuAnsatz = sudokuAnsatzAux;
	setWeight(calculateWeight());
}

SudokuAnsatz::SudokuAnsatz(SudokuSkelleton sudokuSkelletonAux)
{
	sudokuAnsatz = loadByLines(sudokuSkelletonAux);
	setWeight(calculateWeight());
}
