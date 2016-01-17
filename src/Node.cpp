#include <iostream>
#include <cstdio>
#include "Node.hpp"

Node::Node(){}

Node::~Node()
{
	this->v.clear();
}

void Node::addNode(Node* node)
{
	this->v.push_back(node);
}