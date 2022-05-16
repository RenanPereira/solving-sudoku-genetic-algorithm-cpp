#ifndef SUDOKU_H
#define SUDOKU_H

using namespace std;

vector< vector<int> > read_sudoku_from_file(int , string );

int print_sudoku(vector< vector<int> > );

int sudoku_number_of_clues(vector< vector<int> > );

vector< vector<int> > generate_sudoku_by_lines(vector< vector<int> > );

int sudoku_line_weight(vector< vector<int> > , int );

int sudoku_column_weight(vector< vector<int> > , int );

int sudoku_block_weight(vector< vector<int> > , int , int );

int sudoku_lines_OBS(vector< vector<int> > );

int sudoku_columns_OBS(vector< vector<int> > );

int sudoku_blocks_OBS(vector< vector<int> > );

int weight_sudoku_configuration(vector< vector<int> > );

vector< tuple<int, int> > population_weight(vector< vector< vector<int> > > );

int sudoku_tournament(vector< vector< vector<int> > > );

vector< vector< vector<int> > > generate_population(int , vector< vector<int> > );

vector< vector< vector<int> > > generate_descendents(vector< vector<int> > , vector< vector< vector<int> > > , int);

vector< vector<int> > mutate_sudoku(vector< vector<int> > , vector< vector<int> >, double );

vector< vector< vector<int> > > survival_of_the_fittest(vector< vector< vector<int> > > , vector< vector< vector<int> > > , int );


class SudokuSkelleton
{
private: 
	vector< vector<int> > sudokuSkelleton;

public: 
	SudokuSkelleton(int , string );
	void toString();
	int numberOfClues();
	vector< vector<int> > getSkelleton(){ return sudokuSkelleton; }
};


class SudokuAnsatz
{
private:
	vector< vector<int> > sudoku;
    int sudokuWeight;

private:
	void setWeight(int weight){ sudokuWeight = weight; }
	
public:
	vector< vector<int> > loadByLines(SudokuSkelleton);
	SudokuAnsatz(vector< vector<int> >);
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
	vector< vector<int> > getAnsatz(){ return sudoku; }
};



#endif