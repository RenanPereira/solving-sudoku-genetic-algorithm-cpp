// Renan Câmara Pereira
// Solving sudoku puzzles in C++ using the genetic algorithm

#include <iostream>
#include <vector>
#include <omp.h>
#include "sudoku.h"
#include "command_line_args_processor.h"

int main(int argc, char* argv[])
{	
	double start_s = omp_get_wtime();


	int processor_result = command_line_args_processor(argc, argv);
    if ( processor_result==1 ) 
	{
        // If it returns 1, exit with failure code
        return 1;
    }
	else
	{
    	// Continue the main program execution if the function returns 0
    	std::cout << "\nCommands processed successfully, continuing execution...\n";
	}

	double stop_s = omp_get_wtime();

    std::cout << "Run Time: " << (stop_s-start_s) << "\n";

	return 0;
}
