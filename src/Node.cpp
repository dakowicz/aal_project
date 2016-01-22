//Tomasz Dakowicz 261438

#include <iostream>
#include <cstdio>
#include "Node.hpp"

Node::Node(int ID)
{
	this->ID = ID;
}

Node::~Node()
{
	this->v.clear();
}

int Node::getID()
{
	return this->ID;
}

bool Node::isMarked()
{
	return marked;
}

void Node::setMarked(bool val)
{
	this->marked = val;
}

void Node::addNode(Node* node)
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

void Node::printNodes()
{
	for(Node* node : this->v)
	{
		std::cout << node->getID() << " ";
	}
	std::cout << "\n";
}

std::vector<Node*>& Node::getNeighbours()
{
	return this->v;
}

int Node::getNeighboursAmount()
{
	return this->v.size();
}