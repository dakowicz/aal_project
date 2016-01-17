#include <vector>

class Node
{
private: 
	std::vector<Node*> v;
	int ID;

public:
	Node(int ID)
	{
		this->ID = ID;
	}
	
	~Node()
	{
		this->v.clear();
	}

	int getID()
	{
		return this->ID;
	}

	void addNode(Node* node)
	{
		if(node != NULL && this != node)
		{
			for(Node* n : this->v)
			{
				if(n == node)
					return;
			}
			this->v.push_back(node);
		}
	}

	void printNodes()
	{
		for(Node* node : this->v)
		{
			std::cout << node->getID() << " ";
		}
		std::cout << "\n";
	}

	std::vector<Node*>& getNeighbours()
	{
		return this->v;
	}

};