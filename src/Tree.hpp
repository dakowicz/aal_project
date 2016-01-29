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
	void processCoverage(int availablePaths, int algorithm, bool display = true);
	void diameter_method(int& availablePaths, bool display);
	void brutal_method(int& availablePaths, bool display);
	Node* BFSMostCoveredWithTracking(Node* begin, std::vector<Node*>& v);
	Node* BFSMostCovered(Node* begin);
	void BFSGetAllPaths(Node* begin, std::vector< std::vector< Node* > >& vectorOfTracks);
	void printTheWholePath(std::vector<Node*>& v);
	void setMarkedForAll(std::vector<Node*>& v);
	void setMarkedEveryNode(bool val);
	int getCoverage();
	bool isThereThatID(int ID);
	int getNumberOfLeafs();
};