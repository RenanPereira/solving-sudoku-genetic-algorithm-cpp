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
	int population_size = 50;
	double birth_to_population_size_ratio = 0.2;
	int number_descendents = 20;
	int number_generations = 350;
	double max_mutation_fraction_parents = 0.25;
	double max_mutation_fraction_descendents = 1.0;

	//generate sudoku population
	std::vector< std::vector< std::vector<int> > > sudoku_population;
	sudoku_population = Sudoku::generate_population(population_size, sudoku_to_solve);

	//evolution loop
	for (int i = 0; i < number_generations; ++i)
	{	
		std::cout << "\n";
		std::cout << "generation: " <<  i << "\n";
		std::cout << "population size:" << sudoku_population.size() << "\n";
		
		//add new candidates ("births from vacuum")
		const int number_births_from_vacuum = int(birth_to_population_size_ratio*population_size);
		for (int j = 0; j < number_births_from_vacuum; ++j)
		{
			sudoku_population.push_back( Sudoku::generate_by_lines(sudoku_to_solve) );
		}

		//mutate some individuals
		for (int j = 0; j < int(sudoku_population.size()); ++j)
		{
			int x = ( rand() % sudoku_population.size() );
			sudoku_population[x] = Sudoku::mutate(sudoku_to_solve, sudoku_population[x], max_mutation_fraction_parents);
		}

		//generate descendents
		std::vector< std::vector< std::vector<int> > > sudoku_population_descendents;
		sudoku_population_descendents = Sudoku::generate_descendents(
			sudoku_to_solve, 
			sudoku_population, 
			number_descendents
		);

		//mutate descendents
		for (int j = 0; j < int(sudoku_population_descendents.size()); ++j)
		{
			sudoku_population_descendents[j] = Sudoku::mutate(
				sudoku_to_solve, 
				sudoku_population_descendents[j], 
				max_mutation_fraction_descendents
			);
		}

		//combine populations and only keep the fittest, maintaining the population size
		sudoku_population = Sudoku::survival_of_the_fittest(sudoku_population, sudoku_population_descendents, population_size);

		int neo_weight = Sudoku::weight_configuration(sudoku_population[0]);
		std::cout << "weight of the fittest: " << neo_weight << "\n";

		if (neo_weight==0)
		{ 
			break; 
		}
	
	}
	
	if( Sudoku::weight_configuration(sudoku_population[0])==0 )
	{	
		std::cout << "\n";
		std::cout << "solution found! \n";
		Sudoku::print(sudoku_population[0]);
	}
	else
	{	
		std::cout << "\n";
		std::cout << "solution NOT found in this run! \n";
	}
	

	double stop_s = omp_get_wtime();

    std::cout << "Run Time: " << (stop_s-start_s) << "\n";

	return 0;
}
