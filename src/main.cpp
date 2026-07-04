// Renan Câmara Pereira
// Solving sudoku puzzles in C++ using the genetic algorithm

#include <iostream>
#include <vector>
#include <omp.h>
#include "sudoku.h"

int main(void)
{	
	// Use current time as seed for random generator
    //srand((unsigned) time(0));
	srand(1);

	double start_s = omp_get_wtime();


	std::vector< std::vector<int> > sudoku_to_solve = Sudoku::read_from_file(9, "sudoku_9_example_1.dat"); 

	Sudoku::print(sudoku_to_solve);

	std::cout << Sudoku::number_of_clues(sudoku_to_solve) << "\n";

	//parameters to solve sudoku with genetic algorithm
	Sudoku::GeneticAlgorithmParameters params;
	params.population_size = 50;
	params.birth_to_population_size_ratio = 0.2;
	params.number_descendents = 20;
	params.number_generations = 350;
	params.max_mutation_fraction_parents = 0.25;
	params.max_mutation_fraction_descendents = 1.0;

	std::vector< std::vector< std::vector<int> > > sudoku_population =  Sudoku::generate_and_evolve_population(
		sudoku_to_solve,
		params
	);


	double stop_s = omp_get_wtime();

    std::cout << "Run Time: " << (stop_s-start_s) << "\n";

	return 0;
}
