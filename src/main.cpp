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
	

	std::vector< std::vector<int> > sudoku_to_solve = Sudoku::read_from_file(9, "sudoku_example1.dat"); 

	Sudoku::print(sudoku_to_solve);

	std::cout << Sudoku::number_of_clues(sudoku_to_solve) << "\n";

	//parameters to solve sudoku with genetic algorithm
	int N = 50;
	int N_births_from_vacuum = 10;
	int N_descendents = 20;
	int generations = 350;

	//generate sudoku population
	std::vector< std::vector< std::vector<int> > > sudoku_pop = Sudoku::generate_population(N, sudoku_to_solve);

	for (int i = 0; i < generations; ++i)
	{
		std::cout << i << "\t" << sudoku_pop.size() << "\n";

		for (int j = 0; j < N_births_from_vacuum; ++j)
		{
			sudoku_pop.push_back( Sudoku::generate_by_lines(sudoku_to_solve) );
		}

		//mutate some individuals
		for (int j = 0; j < int(sudoku_pop.size()); ++j)
		{
			int X = ( rand() % sudoku_pop.size() );
			sudoku_pop[X] = Sudoku::mutate(sudoku_to_solve, sudoku_pop[X], 0.25);
		}

		//generate descendents
		std::vector< std::vector< std::vector<int> > > sudoku_pop_descendents;
		sudoku_pop_descendents = Sudoku::generate_descendents(sudoku_to_solve, sudoku_pop, N_descendents);
		//mutate descendents
		for (int j = 0; j < int(sudoku_pop_descendents.size()); ++j)
		{
			sudoku_pop_descendents[j] = Sudoku::mutate(sudoku_to_solve, sudoku_pop_descendents[j], 1.0);
		}

		sudoku_pop = Sudoku::survival_of_the_fittest(sudoku_pop, sudoku_pop_descendents, N);

		int neo_weight = Sudoku::weight_configuration(sudoku_pop[0]);

		std::cout << "weight of the fittest individual: " << neo_weight << "\n";
		if (neo_weight==0){ break; }
	
	}
	
	Sudoku::print(sudoku_pop[0]);


	double stop_s = omp_get_wtime();

    std::cout << "Run Time: " << (stop_s-start_s) << "\n";

	return 0;
}



