#include <iostream>
#include <cstdio>
#include "Node.hpp"
#include "Tree.hpp"

int main()
{
	int n, a, b;
	Tree tree;

	std::cin >> n;

	while( n > 1)
	{
		std::cin >> a >> b;

		Node* source = tree.getNode(a);
		Node* dest = tree.getNode(b);

		source->addNode(dest);
		dest->addNode(source);
		// source->printNodes();
		n--;
	}

	tree.BFS();

	return 0;
}