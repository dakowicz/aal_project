//Tomasz Dakowicz 261438

#include <map>
#include <queue>
#include <iostream>
#include "Node.hpp"

class Tree
{
private:
	std::map<int, Node*> mapOfNodes;
	std::vector<Node*> leafs;

public:

	static const int BRUTAL_METHOD = 1;
	static const int DIAMETER_METHOD = 2;

	Tree();
	~Tree();

	Node* getNode(int ID);
	void findLeafs();
	Node* BFSFarthestNodeWithTracking(Node* begin, std::vector<Node*>& v);
	Node* BFSFarthestNode(Node* begin);
	void processCoverage(int& availablePaths, int& algorithm);
	void diameter_method(int& availablePaths);
	void brutal_method(int& availablePaths);
	void BFSGetAllPaths(Node* begin, std::vector< std::vector< Node* > >& vectorOfTracks);
	void printTheWholePath(std::vector<Node*>& v);
	void setMarkedForAll(std::vector<Node*>& v);
	int getCoverage();
};