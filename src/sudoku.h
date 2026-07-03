#ifndef SUDOKU_H
#define SUDOKU_H

namespace Sudoku
{
	std::vector< std::vector<int> > read_from_file(int , std::string );

	int print(std::vector< std::vector<int> > );

	int number_of_clues(std::vector< std::vector<int> > );

	std::vector< std::vector<int> > generate_by_lines(std::vector< std::vector<int> > );

	int line_weight(std::vector< std::vector<int> > , int );

	int column_weight(std::vector< std::vector<int> > , int );

	int block_weight(std::vector< std::vector<int> > , int , int );

	int lines_observable(std::vector< std::vector<int> > );

	int columns_observable(std::vector< std::vector<int> > );

	int blocks_observable(std::vector< std::vector<int> > );

	int weight_configuration(std::vector< std::vector<int> > );

	std::vector< std::tuple<int, int> > population_weight(std::vector< std::vector< std::vector<int> > > );

	int tournament(std::vector< std::vector< std::vector<int> > > );

	std::vector< std::vector< std::vector<int> > > generate_population(int , std::vector< std::vector<int> > );

	std::vector< std::vector< std::vector<int> > > generate_descendents(
		std::vector< std::vector<int> > , 
		std::vector< std::vector< std::vector<int> > > , 
		int
	);

	std::vector< std::vector<int> > mutate(
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