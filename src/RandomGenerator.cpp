#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator(){}

RandomGenerator::~RandomGenerator(){}

void RandomGenerator::generate()
{
	srand (time(NULL));

	int nodesAmount = rand() % 1000 + 100;
	std::cout << "losowe n = " << nodesAmount << '\n';

	int paths = rand () % 100 + 10;
	std::cout << "losowa liczba sciezek = " << paths << '\n';

	int n = nodesAmount;
	int s, d;

	while(n > 1)
	{
		s = rand() % (nodesAmount+1) + 1;
		Node* source = tree.getNode(s);

		d = rand() % (nodesAmount+1) + 1;
		Node* dest = tree.getNode(d);

		source->addNode(dest);
		dest->addNode(source);

		n--;
	}

	std::cout << "Otrzymane sciezki metoda brutalna:\n";

	tree.processCoverage(paths, Tree::BRUTAL_METHOD);

	int coverage = tree.getCoverage();

	std::cout << "Otrzymane pokrycie grafu metoda brutalna: "<< coverage << "/" << nodesAmount <<"\n";

}

	