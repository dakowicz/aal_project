//Tomasz Dakowicz 261438

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Tree.hpp"

static const char* INPUT = "--input";
static const char* RANDOM = "--random";
static const char* COMPLEX = "--complex";


//function responsible for manual input mode
void inputMethod();
//function responsible for random input data generation mode
void randomMethod();
//function responsible for custom settings mode
void complexMethod();
//command was not recognized
void wrongCommand();



int main(int argc, char** argv)
{
	if(argc == 2)
	{
		if(strcmp(argv[1], INPUT) == 0)
			inputMethod();
		else if(strcmp(argv[1], RANDOM) == 0)
			randomMethod();
		else if(strcmp(argv[1], COMPLEX) == 0)
			complexMethod();
		else
			wrongCommand();
	}

	return 0;
}

void inputMethod()
{
	int s, d;
	int numberOfNodes, availablePaths;
	int algorithm;
	Tree tree;

	std::cout << "Zadanie: T2 - Mrowki\n";
	std::cout << "Wybierz algorytm: \n";
	std::cout << "1. Rozwiazanie brutalne\n";
	std::cout << "2. Rozwiazanie ze srednica grafu\n";

	std::cin >> algorithm;

	std::cout << "Podaj liczbe mrowisk:\n";
	std::cin >> numberOfNodes;

	std::cout << "Podaj liczbe mozliwych sciezek:\n";
	std::cin >> availablePaths;

	std::cout << "Wypisz wszystkie polaczenia miedzy mrowiskami:\n";
	int n = numberOfNodes;
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

	std::cout << "\nOtrzymane sciezki:\n";

	tree.findLeafs();
	tree.processCoverage(availablePaths, algorithm);

	int coverage = tree.getCoverage();

	std::cout << "\nOtrzymane pokrycie grafu: "<< coverage << "/" << numberOfNodes <<"\n";
	std::cout << tree.getNumberOfLeafs();
}


void generateConnections(Tree& tree, int n, bool display = true)
{
	int numberOfNodes = n;
	int s, d;
	while(n > 1)
	{
		//find random existing node
		while( (s = rand() % (numberOfNodes) + 1) && tree.isThereThatID(s) == false);
		Node* source = tree.getNode(s);

		//find random non-existing node
		while( (d = rand() % (numberOfNodes) + 1) && tree.isThereThatID(d) == true);
		Node* dest = tree.getNode(d);

		if(display)
			std::cout << s << " " << d << '\n';

		//connect
		source->addNode(dest);
		dest->addNode(source);
		n--;
	}
}

void randomMethod()
{
	Tree tree;
	srand (time(NULL));

	std::cout << "Zadanie: T2 - Mrowki\n";

	int numberOfNodes, paths;

	std::cout << "Podaj liczbe mrowisk:\n";
	std::cin >> numberOfNodes;

	std::cout << "Podaj liczbe mozliwych sciezek:\n";
	std::cin >> paths;

	//add base node
	tree.getNode(1);

	std::cout << "Wygenerowano nastepujace polaczenia:\n";
	generateConnections(tree, numberOfNodes);
	tree.findLeafs();

	//brutal method first
	std::cout << "\nOtrzymane sciezki metoda brutalna:\n";

	int method = Tree::BRUTAL_METHOD;
	tree.processCoverage(paths, method);

	int coverageBrutalMethod = tree.getCoverage();

	std::cout << "\n";

	//resetting the markers
	tree.setMarkedEveryNode(false);

	//time for optimized method
	std::cout << "Otrzymane sciezki metoda optymalna:\n";

	method = Tree::DIAMETER_METHOD;
	tree.processCoverage(paths, method);

	int coverageOptimizedMethod = tree.getCoverage();

	std::cout << "\n";

	//comparison between methods
	std::cout << "Otrzymane pokrycie grafu metoda brutalna: "<< coverageBrutalMethod << "/" << numberOfNodes <<"\n";
	std::cout << "Otrzymane pokrycie grafu metoda optymalna: "<< coverageOptimizedMethod << "/" << numberOfNodes <<"\n";
}

double convertToMilisecondsFromClocks(clock_t clocks)
{
    return static_cast < double >( clocks ) / (CLOCKS_PER_SEC / 1000);
}


void runTest(std::vector<int>& numberOfNodes, std::vector<int>& paths, std::vector<int>& numberOfLeafs, std::vector<double>& executionTime, int N, int P, int method)
{
	Tree tree;
	clock_t beginTime;

	numberOfNodes.push_back(N);
	paths.push_back(P);

	//add base node
	tree.getNode(1);

	//add connections
	generateConnections(tree, N, false);
	
	//find leafs
	tree.findLeafs();
	numberOfLeafs.push_back(tree.getNumberOfLeafs());

	//get execution time for brutal method
	beginTime = clock();

	//execute
	tree.processCoverage(P, method, false);
	executionTime.push_back(convertToMilisecondsFromClocks(clock() - beginTime));

	std::cout << "Zakonczono obliczenia testu\n";
}

double calculateQ(int N, int P, int L, double executionTime, int middleN, int middleP, int middleL, double middleTime, int method)
{
	double middleQuotient;

	if(method == Tree::BRUTAL_METHOD)
	{
		middleQuotient = ((middleL*middleL) * ( middleP + 2 * middleN)) / middleTime;
		return (executionTime / ((L*L) * (P + 2 * N)) ) * middleQuotient;
	}
	if(method == Tree::DIAMETER_METHOD)
	{
		middleQuotient = (4 * middleN * middleP) / middleTime;
		return (executionTime / (4 * N * P)) * middleQuotient;
	}
} 

void complexMethod()
{
	srand (time(NULL));
	int method, N, P, diff;
	double q;

	std::cout << "Zadanie: T2 - Mrowki\n";
	std::cout << "Wybierz algorytm: \n";
	std::cout << "1. Rozwiazanie brutalne\n";
	std::cout << "2. Rozwiazanie ze srednica grafu\n";

	std::cin >> method;

	std::cout << "Podaj startowe N:\n";
	std::cin >> N;

	std::cout << "Podaj tempo wzrosu N:\n";
	std::cin >> diff;

	std::cout << "Podaj stale P:\n";
	std::cin >> P;

	int tests;
	std::vector<int> numberOfLeafs, numberOfNodes, paths;
	std::vector<double> executionTime;

	//10 tests
	for (int i = 0; i < 10; ++i)
	{
		runTest(numberOfNodes, paths, numberOfLeafs, executionTime, N, P, method);
		N += diff;
	}

	//get middle result
	int middleN = numberOfNodes[4];
	int middleP = paths[4];
	int middleL = numberOfLeafs[4];
	double middleTime = executionTime[4];

	std::cout << "Prezentacja pomiarow:\n";
	std::cout << "N" << "\t" << "P" << "\t" << "L" << "\t" << "t[N,P]" << "\t" << "q[N,P]" << "\n";
	for (int i = 0; i < 10; ++i)
	{
		q = calculateQ(numberOfNodes[i], paths[i], numberOfLeafs[i], executionTime[i], middleN, middleP, middleL, middleTime, method);
		std::cout << numberOfNodes[i] << "\t" << paths[i] << "\t" << numberOfLeafs[i] << "\t" << executionTime[i] << "\t" << q << "\n" ; 
	}
}

void wrongCommand()
{
	std::cout << "Wprowadzono bledny tryb programu\n";
	std::cout << "Zamknieto dzialanie aplikacji\n";
}