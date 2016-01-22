//Tomasz Dakowicz 261438

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "Tree.hpp"
#include "RandomGenerator.hpp"

static const char* INPUT = "--input";
static const char* RANDOM = "--random";
static const char* COMPLEX = "--complex";


//function responsible for manual input mode
void input_method();
//function responsible for random input data generation mode
void random_method();
//function responsible for custom settings mode
void complex_method();
//command was not recognized
void wrong_command();



int main(int argc, char** argv)
{
	if(argc == 2)
	{
		if(strcmp(argv[1], INPUT) == 0)
			input_method();
		else if(strcmp(argv[1], RANDOM) == 0)
			random_method();
		else if(strcmp(argv[1], COMPLEX) == 0)
			complex_method();
		else
			wrong_command();
	}

	return 0;
}

void input_method()
{
	int s, d;
	int nodesAmount, availablePaths;
	int algorithm;
	Tree tree;

	std::cout << "Zadanie: T2 - Mrowki\n";
	std::cout << "Wybierz algorytm: \n";
	std::cout << "1. Rozwiazanie brutalne\n";
	std::cout << "2. Rozwiazanie ze srednica grafu\n";

	std::cin >> algorithm;

	std::cout << "Podaj liczbe mrowisk:\n";
	std::cin >> nodesAmount;

	std::cout << "Podaj liczbe N mozliwych sciezek:\n";
	std::cin >> availablePaths;

	std::cout << "Wypisz wszystkie polaczenia miedzy mrowiskami:\n";
	int n = nodesAmount;
	while(n > 1)
	{
		std::cin >> s >> d;
		Node* source = tree.getNode(s);
		Node* dest = tree.getNode(d);
		//add connections
		source->addNode(dest);
		dest->addNode(source);
		n--;
	}

	std::cout << "Otrzymane sciezki:\n";

	tree.processCoverage(availablePaths, algorithm);

	int coverage = tree.getCoverage();

	std::cout << "Otrzymane pokrycie grafu: "<< coverage << "/" << nodesAmount <<"\n";
}

void random_method()
{
	RandomGenerator generator;
	generator.generate();
}

void complex_method()
{

}


void wrong_command()
{
	std::cout << "Wprowadzono bledny tryb programu\n";
	std::cout << "Zamknieto dzialanie aplikacji\n";
}