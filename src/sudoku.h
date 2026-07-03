#ifndef SUDOKU_H
#define SUDOKU_H

namespace Sudoku
{
	std::vector< std::vector<int> > read_sudoku_from_file(int , std::string );

	int print_sudoku(std::vector< std::vector<int> > );

	int sudoku_number_of_clues(std::vector< std::vector<int> > );

	std::vector< std::vector<int> > generate_sudoku_by_lines(std::vector< std::vector<int> > );

	int sudoku_line_weight(std::vector< std::vector<int> > , int );

	int sudoku_column_weight(std::vector< std::vector<int> > , int );

	int sudoku_block_weight(std::vector< std::vector<int> > , int , int );

	int sudoku_lines_OBS(std::vector< std::vector<int> > );

	int sudoku_columns_OBS(std::vector< std::vector<int> > );

	int sudoku_blocks_OBS(std::vector< std::vector<int> > );

	int weight_sudoku_configuration(std::vector< std::vector<int> > );

	std::vector< std::tuple<int, int> > population_weight(std::vector< std::vector< std::vector<int> > > );

	int sudoku_tournament(std::vector< std::vector< std::vector<int> > > );

	std::vector< std::vector< std::vector<int> > > generate_population(int , std::vector< std::vector<int> > );

	std::vector< std::vector< std::vector<int> > > generate_descendents(
		std::vector< std::vector<int> > , 
		std::vector< std::vector< std::vector<int> > > , 
		int
	);

	std::vector< std::vector<int> > mutate_sudoku(
		std::vector< std::vector<int> > , 
		std::vector< std::vector<int> >, 
		double 
	);

	std::vector< std::vector< std::vector<int> > > survival_of_the_fittest(
		std::vector< std::vector< std::vector<int> > > , 
		std::vector< std::vector< std::vector<int> > > , 
		int 
	);
}

#endif