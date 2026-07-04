#ifndef SUDOKU_H
#define SUDOKU_H

namespace Sudoku
{

	struct GeneticAlgorithmParameters
{
    int population_size = 50;

    // Fraction of the population replaced by randomly generated individuals
    double birth_to_population_size_ratio = 0.2;

    // Number of offspring generated each generation
    int number_descendents = 20;

    // Maximum number of generations
    int number_generations = 350;

    // Maximum mutation intensity applied to existing population
    double max_mutation_fraction_parents = 0.25;

    // Maximum mutation intensity applied to offspring
    double max_mutation_fraction_descendents = 1.0;
};

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

	int battle(std::vector< std::vector< std::vector<int> > > );

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

	std::vector< std::vector< std::vector<int> > > generate_and_evolve_population(
		std::vector< std::vector<int> > ,
		GeneticAlgorithmParameters 
	);
}

#endif