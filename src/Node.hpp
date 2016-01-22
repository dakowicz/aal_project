//Tomasz Dakowicz 261438

#include <vector>

class Node
{
private: 
	std::vector<Node*> v;
	int ID;
	bool marked;

public:
	Node(int ID);
	~Node();

	int getID();
	bool isMarked();
	void setMarked(bool val);
	void addNode(Node* node);
	void printNodes();
	std::vector<Node*>& getNeighbours();
	int getNeighboursAmount();
};