#include <iostream>
#include "sudoku.h"
#include "command_line_args_processor.h"


int command_line_args_processor(int argc, char* argv[])
{	
	std::string solve_sudoku = "solve-sudoku";
	std::string solve_sudoku_9_example = "solve-sudoku-9-example";

	// Handle command line input
    if (argc > 1) 
	{
        std::string command = argv[1];
        // Check for the commands
        if (command == solve_sudoku) 
		{	
			int sudoku_size = std::stoi(argv[2]);
			std::string sudoku_filename = argv[3];

			Sudoku::GeneticAlgorithmParameters params;
			Sudoku::solve(sudoku_size, sudoku_filename, params);
        } 
		else if ( command == solve_sudoku_9_example )
		{
			//parameters to solve sudoku with genetic algorithm
			Sudoku::GeneticAlgorithmParameters params;
			params.population_size = 50;
			params.birth_to_population_size_ratio = 0.2;
			params.number_descendents = 20;
			params.number_generations = 350;
			params.max_mutation_fraction_parents = 0.25;
			params.max_mutation_fraction_descendents = 1.0;

			const int sudoku_size = 9;
			const std::string sudoku_filename = "sudoku_9_example_1.dat";

			Sudoku::solve(sudoku_size, sudoku_filename, params);
		}
		else 
		{
            std::cerr << "Unknown command: " << command << std::endl;
            return 1;
        }
    }

	return 0;
}
