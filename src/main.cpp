//Tomasz Dakowicz 261438

#include <iostream>
#include <cstdio>
#include "Tree.hpp"

int main(int argc, char** argv)
{
	if(argc == 2)
		printf("2\n");
	if(argc == 3)
		printf("3\n");

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