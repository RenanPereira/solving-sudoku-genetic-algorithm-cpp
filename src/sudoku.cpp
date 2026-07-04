#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <omp.h>
#include <algorithm>
#include "sudoku.h"

using std::string;
using std::vector;
using std::tuple;


//function that reads sudoku from file to a vector of vectors
vector< vector<int> > Sudoku::read_from_file(int sudoku_lenght, string file_name)
{   
    vector< vector<int> > sudoku;

    //read file to vector of vectors
    std::ifstream cin(file_name);
    std::string line;
    while( std::getline(cin, line) ) 
    {	
    	vector<int> sudoku_lin = {};

        std::istringstream ss(line);
		while (ss >> line)
		{ 
			sudoku_lin.push_back( stoi(line) ); 
		}

        sudoku.push_back( sudoku_lin );
    }

    //test if the size of the sudoku the equal to the sudoku lenght
    int aux = 1 + (sudoku.size() - sudoku_lenght);
    if ( aux!=1 )
   	{ 	
   		printf("Problem in the sudoku file!\n");
    	abort(); 
    }
    for (int i = 0; i < int(sudoku.size()); ++i)
    {	
    	aux = 1 + (sudoku[i].size() - sudoku_lenght);
    	if ( aux!=1 )
    	{	
    		printf("Problem in the sudoku file!\n");
    		abort();
    	}
    }

    return sudoku;   
}

//function that prints a given sudoku
int Sudoku::print(vector< vector<int> > sudoku)
{   
    for (int i = 0; i < int(sudoku.size()); ++i)
    {
    	for (int j = 0; j < int(sudoku[i].size()); ++j)
    	{	
    		printf("%i ", sudoku[i][j]);
    	}
    	printf("\n");
    }

    return 0;   
}

//function that returns the number of clues in the sudoku
int Sudoku::number_of_clues(vector< vector<int> > sudoku_skeleton)
{
	int clues = 0;
	for (int i = 0; i < int(sudoku_skeleton.size()); ++i)
	{	
		for (int j = 0; j < int(sudoku_skeleton[i].size()); ++j)
		{
			if ( sudoku_skeleton[i][j]!=0 )
			{
				clues = clues + 1;
			}
		}
	}

	return clues;
}

//function that generates a sudoku given an initial sudoku filled with clues
vector< vector<int> > Sudoku::generate_by_lines(vector< vector<int> > sudoku_skeleton)
{   
    vector< vector<int> > sudoku = sudoku_skeleton;

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
    		if (add_element==true)
			{ 
				guesses.push_back( element ); 
			}
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

//function that calculate the lines weight of a given sudoku
int Sudoku::line_weight(vector< vector<int> > sudoku, int line)
{	
	vector<int> sudoku_lin = sudoku[line];

	int weight = 0;
	int sum_count = 0;
	for (int i = 0; i < int(sudoku_lin.size()); ++i)
	{
		int aux = count(sudoku_lin.begin(), sudoku_lin.end(), i+1);
		weight = weight + pow(aux-1,2);
		sum_count = sum_count + aux;
	}

	if ( sum_count!=int(sudoku.size()) )
	{ 
		printf("Problem in line_weight! Counting not equal to sudoku lenght!\n"); 
		abort(); 
	}

	return weight;
}

//function that calculate the columns weight of a given sudoku
int Sudoku::column_weight(vector< vector<int> > sudoku, int column)
{	
	vector<int> sudoku_col(sudoku.size(),0);
	for (int i = 0; i < int(sudoku.size()); ++i)
	{
		sudoku_col[i] = sudoku[i][column];
	}

	int weight = 0;
	int sum_count = 0;
	for (int i = 0; i < int(sudoku_col.size()); ++i)
	{
		int aux = count(sudoku_col.begin(), sudoku_col.end(), i+1);
		weight = weight + pow(aux-1,2);
		sum_count = sum_count + aux;
	}

	if ( sum_count!=int(sudoku.size()) )
	{ 
		printf("Problem in column_weight! Counting not equal to sudoku lenght!\n"); 
		abort(); 
	}

	return weight;
}

//function that calculate the block weight of a given sudoku
int Sudoku::block_weight(vector< vector<int> > sudoku, int block_line, int block_column)
{	
	//Lenght of block: square root of the sudoku size, by definition
	int minor_square_size = int( sqrt( sudoku.size() ) );

	if ( block_line<0 || block_line>minor_square_size )
	{ 
		printf("Sudoku block line out of bounds!\n"); abort(); 
	}
	if ( block_column<0 || block_column>minor_square_size )
	{ 
		printf("Sudoku block column out of bounds!\n"); 
		abort(); 
	}

	int xx = block_line*minor_square_size;
	int yy = block_column*minor_square_size;

	vector<int> sudoku_block(sudoku.size(),0);
	int aux = 0;
	for (int i = xx; i < xx+minor_square_size; ++i)
	{
		for (int j = yy; j < yy+minor_square_size; ++j)
		{	
			sudoku_block[aux] = sudoku[i][j];
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

	if ( sum_count!=int(sudoku.size()) )
	{ 
		printf("Problem in block_weight! Counting not equal to sudoku lenght!\n"); 
		abort(); 
	}


	return weight;
}

//function that calculate the lines observable of a given sudoku
int Sudoku::lines_observable(vector< vector<int> > sudoku)
{
	int obs = 0;
	for (int i = 0; i < int(sudoku.size()); ++i)
	{
		obs = obs + line_weight(sudoku, i);
	}

	return obs;
}

//function that calculate the columns observable of a given sudoku
int Sudoku::columns_observable(vector< vector<int> > sudoku)
{
	int obs = 0;
	for (int i = 0; i < int(sudoku.size()); ++i)
	{
		obs = obs + column_weight(sudoku, i);
	}

	return obs;
}

//function that calculate the blocks observable of a given sudoku
int Sudoku::blocks_observable(vector< vector<int> > sudoku)
{	
	int minor_square_size = int( sqrt(sudoku.size()) );
	int obs = 0;

	for (int l = 0; l < minor_square_size; ++l)
	{	
		for (int c = 0; c < minor_square_size; ++c)
		{
			obs = obs + block_weight(sudoku, l, c);
		}
	}

	return obs;
}

//function that calculates the total weight of a sudoku
int Sudoku::weight_configuration(vector< vector<int> > sudoku)
{
	int W = 0;
	W = W + columns_observable(sudoku);
	W = W + blocks_observable(sudoku);

	return W;
}

//function that mutates a given sudoku
vector< vector<int> > Sudoku::mutate(
	vector< vector<int> > sudoku_skeleton, 
	vector< vector<int> > sudoku, 
	double max_mutation_fraction
)
{	
	vector< vector<int> > mutated_sudoku = sudoku;

	//calculate the maximum number of mutations
	int max_number_mutations = int( max_mutation_fraction*( pow(sudoku_skeleton.size(),2) - number_of_clues(sudoku_skeleton) ) );

	if (max_number_mutations>0)
	{
		//calculate the number of mutations randomly
		int number_mutations = ( rand() % max_number_mutations + 1 );

		//apply mutations
		for (int i = 0; i < number_mutations; ++i)
		{
			//randomly choose a line to mutate
			int L = ( rand() % sudoku_skeleton.size() );

			//randomly choose two elements in the line to exchange position
			bool generate = true;
			while ( generate==true )
			{
				int C1 = ( rand() % sudoku_skeleton.size() );
				int C2 = C1;
				while ( C2==C1 ){	C2 = ( rand() % sudoku_skeleton.size() ); }

				//only apply mutation on top of clues
				if ( sudoku_skeleton[L][C1]==0 && sudoku_skeleton[L][C2]==0 )
				{
					int sudoku_weight_before_mutation = weight_configuration(mutated_sudoku);
					int aux1 = mutated_sudoku[L][C1];
					int aux2 = mutated_sudoku[L][C2];
					mutated_sudoku[L][C1] = aux2;
					mutated_sudoku[L][C2] = aux1;
					int sudoku_weight_after_mutation = weight_configuration(mutated_sudoku);

					//only accept mutation if the weight after mutation is smaller
					if ( sudoku_weight_after_mutation>sudoku_weight_before_mutation )
					{
						mutated_sudoku[L][C1] = aux1;
						mutated_sudoku[L][C2] = aux2;
					}
					generate=false;
				}
			}
		}
	}

	return mutated_sudoku;
}	

//calculate population weight
vector< tuple<int, int> > Sudoku::population_weight(vector< vector< vector<int> > > sudoku_population)
{
	vector< tuple<int, int> > pop_weight;
	for (int i = 0; i < int(sudoku_population.size()); ++i)
	{	
		tuple<int, int> aux = std::make_tuple( weight_configuration(sudoku_population[i]) , i );
		pop_weight.push_back( aux );
	}

	return pop_weight;
}

//sudoku battle
int Sudoku::battle(vector< vector< vector<int> > > sudoku_population)
{
	int warrior_1 = ( rand() % sudoku_population.size() );
	int warrior_2 = ( rand() % sudoku_population.size() );
	
	while(warrior_2==warrior_1)
	{ 
		warrior_2 = ( rand() % sudoku_population.size() ); 
	}

	int weight_warrior_1 = weight_configuration(sudoku_population[warrior_1]);
	int weight_warrior_2 = weight_configuration(sudoku_population[warrior_2]);

	int winner = 0;
	if ( weight_warrior_1<weight_warrior_2 )
	{ 
		winner = warrior_1; 
	}
	else
	{ 
		winner = warrior_2; 
	}

	return winner;
}

//generate population
vector< vector< vector<int> > > Sudoku::generate_population(int population_size, vector< vector<int> > sudoku_skeleton)
{
	vector< vector< vector<int> > > population;
	for (int i = 0; i < population_size; ++i)
	{
		population.push_back( generate_by_lines(sudoku_skeleton) );
	}

	return population;
}

//increase the population by generating descendants
vector< vector< vector<int> > > Sudoku::generate_descendents(
	vector< vector<int> > sudoku_skeleton, 
	vector< vector< vector<int> > > sudoku_population, 
	int number_descendents
)
{
	vector< vector< vector<int> > > sudoku_population_descendents;
	for (int i = 0; i < number_descendents; ++i)
	{
		//create couple
		vector<int> partners;
		partners.push_back( battle(sudoku_population) );
		partners.push_back( battle(sudoku_population) );
		while( partners[0]==partners[1] )
		{ 
			partners[0] = battle(sudoku_population); 
		}
		
		//the son is constructed by chosing lines, randomly, from the parents, guaranteeing that the overall line observable is conserved and equal to zero
		vector< vector<int> > sudoku_descendent;
		for (int j = 0; j < int(sudoku_skeleton.size()); ++j)
		{
			int parent = partners[( rand() % 2 )];
			sudoku_descendent.push_back( sudoku_population[parent][j] );
		}
		sudoku_population_descendents.push_back( sudoku_descendent );
	}

	return sudoku_population_descendents;
}

//after the population generates descedents, only the fittest surivive
vector< vector< vector<int> > > Sudoku::survival_of_the_fittest(
	vector< vector< vector<int> > > sudoku_population, 
	vector< vector< vector<int> > > sudoku_population_descendents, 
	int population_size
)
{	
	//add parents and descendents to an over population
	vector< vector< vector<int> > > sudoku_overpopulation;
	for (int i = 0; i < int(sudoku_population.size()); ++i)
	{
		sudoku_overpopulation.push_back( sudoku_population[i] );
	}
	for (int i = 0; i < int(sudoku_population_descendents.size()); ++i)
	{
		sudoku_overpopulation.push_back( sudoku_population_descendents[i] );
	}

	//calculate cost function of the overpopulation
	vector< tuple<int, int> > sudoku_overpop_weight = population_weight(sudoku_overpopulation);
	sort(sudoku_overpop_weight.begin(), sudoku_overpop_weight.end());

	//create new population
	vector< vector< vector<int> > > sudoku_newpopulation;
	for (int i = 0; i < population_size; ++i)
	{
		int sudoku_surviver_index = std::get<1>(sudoku_overpop_weight[i]);
		sudoku_newpopulation.push_back( sudoku_overpopulation[sudoku_surviver_index] );
	}

	return sudoku_newpopulation;
}

std::vector< std::vector< std::vector<int> > > Sudoku::generate_and_evolve_population(
	std::vector< std::vector<int> > sudoku_to_solve,
	GeneticAlgorithmParameters params
)
{	
	int population_size = params.population_size;
	double birth_to_population_size_ratio = params.birth_to_population_size_ratio;
	int number_descendents = params.number_descendents;
	int number_generations = params.number_generations;
	double max_mutation_fraction_parents = params.max_mutation_fraction_parents;
	double max_mutation_fraction_descendents = params.max_mutation_fraction_descendents;
	
	//generate sudoku population
	std::vector< std::vector< std::vector<int> > > sudoku_population;
	sudoku_population = Sudoku::generate_population(population_size, sudoku_to_solve);

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

	return sudoku_population;
}
