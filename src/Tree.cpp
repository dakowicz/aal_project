//Tomasz Dakowicz 261438

#include "Tree.hpp"

Tree::Tree(){}

Tree::~Tree()
{
	this->mapOfNodes.clear();
	this->leafs.clear();
}	

Node* Tree::getNode(int ID)
{
	if(mapOfNodes[ID] == NULL)
		mapOfNodes[ID] = new Node(ID);

	return mapOfNodes[ID];
}

void Tree::findLeafs()
{
	for(auto& node : mapOfNodes)
	{
		//leaf of the tree
		if(node.second->getNeighboursAmount() == 1)
			this->leafs.push_back(node.second);
	}
}

Node* Tree::BFSFarthestNodeWithTracking(Node* begin, std::vector<Node*>& v)
{
	std::queue<Node*> q;
	std::map<Node*, int> mapOfDistance;
	std::map<Node*, bool> mapOfVisitedState;
	std::map<Node*, Node*> mapOfAncedents;
	
	//current farthest node - it's the starting node
	Node* farthest = begin;

	q.push(begin);
	mapOfDistance[begin] = 0;
	mapOfVisitedState[begin] = true;
	mapOfAncedents[begin] = begin;

	while(!q.empty())
	{
		Node* parent = q.front();
		q.pop();

		// std::cout << parent->getID() << std::endl;

		for(Node* node : parent->getNeighbours())
		{
			if(mapOfVisitedState[node] == false)
			{
				q.push(node);
				mapOfVisitedState[node] = true;
				mapOfDistance[node] = mapOfDistance[parent] + 1;
				mapOfAncedents[node] = parent;

				//check if we found new farthest node
				//farthest one -> its the node with currently highest distance && not marked
				if(mapOfDistance[node] > mapOfDistance[farthest] && node->isMarked() == false)
					farthest = node;
			}
		}
	}

	Node* track = farthest;

	//save path to the vector
	while(mapOfAncedents[track] != track)
	{
		v.push_back(track);
		track = mapOfAncedents[track];
	}
	//last one
	v.push_back(track);

	return farthest;
}

Node* Tree::BFSFarthestNode(Node* begin)
{
	std::queue<Node*> q;
	std::map<Node*, int> mapOfDistance;
	std::map<Node*, bool> mapOfVisitedState;
	
	//current farthest node - it's the starting node
	Node* farthest = begin;

	q.push(begin);
	mapOfDistance[begin] = 0;
	mapOfVisitedState[begin] = true;

	while(!q.empty())
	{
		Node* parent = q.front();
		q.pop();

		// std::cout << parent->getID() << std::endl;

		for(Node* node : parent->getNeighbours())
		{
			if(mapOfVisitedState[node] == false)
			{
				q.push(node);
				mapOfVisitedState[node] = true;
				mapOfDistance[node] = mapOfDistance[parent] + 1;

				//check if we found new farthest node
				//farthest one -> its the node with currently highest distance && not marked
				if(mapOfDistance[node] > mapOfDistance[farthest] && node->isMarked() == false)
					farthest = node;
			}
		}
	}

	return farthest;
}


void Tree::processCoverage(int& availablePaths, int& algorithm)
{
	if(algorithm == DIAMETER_METHOD)
		diameter_method(availablePaths);
	else if(algorithm == BRUTAL_METHOD)
		brutal_method(availablePaths);
}

void Tree::diameter_method(int& availablePaths)
{
	//find all leafs in the tree
	findLeafs();

	//start from first not marked leaf
	for(Node* node : this->leafs)
	{
		if(availablePaths == 0)
			break;

		if(node->isMarked() == false)
		{
			//find current farthest node
			Node* sourceNode = this->BFSFarthestNode(node);

			//find the diameter of the current tree
			//and save the track into vector
			std::vector<Node*> track;
			Node* destinationNode = this->BFSFarthestNodeWithTracking(sourceNode, track);

			//set all nodes in the path as marked 
			setMarkedForAll(track);

			//print the track
			printTheWholePath(track);

			//the new path has been created
			availablePaths--;
		}
	}
}

void Tree::brutal_method(int& availablePaths)
{
	//find all leafs
	findLeafs();

	//vector of vectors for all paths between leafs
	std::vector< std::vector<Node*> > tracks;

	//review all the leafs
	for(Node* node : this->leafs)
	{
		//find ways for every other leaf
		BFSGetAllPaths(node, tracks);
	}

	//select tracks with the currently highest coverage
	while(availablePaths--)
	{
		int maxCoverage = 0;
		std::vector<Node*>* maxCoverageTrack;

		for(std::vector<Node*>& v : tracks)
		{
			int notCoveredNodesInTrack = 0;
			for(Node* node : v)
			{
				if(node->isMarked() == false)
					notCoveredNodesInTrack++;
			}

			//check if it is new pretendent
			if(notCoveredNodesInTrack > maxCoverage)
			{
				maxCoverage = notCoveredNodesInTrack;
				maxCoverageTrack = &v;
			}
		}

		//if everything covered -> break
		if(maxCoverage == 0)
			break;

		//apply the best track
		setMarkedForAll(*maxCoverageTrack);
		//print the best track
		printTheWholePath(*maxCoverageTrack);
	}
}

void Tree::BFSGetAllPaths(Node* begin, std::vector< std::vector< Node* > >& vectorOfTracks)
{
	std::queue <Node*> q;
	std::map<Node*, bool> mapOfVisitedState;
	std::map<Node*, Node*> mapOfAncedents;

	q.push(begin);
	mapOfVisitedState[begin] = true;
	mapOfAncedents[begin] = begin;

	while(!q.empty())
	{
		Node* parent = q.front();
		q.pop();

		for(Node* node : parent->getNeighbours())
		{
			if(mapOfVisitedState[node] == false)
			{
				q.push(node);
				mapOfVisitedState[node] = true;
				mapOfAncedents[node] = parent;
			}
		}
	}

	//generate all the paths between starting node and other leafs

	for(Node* leaf : this->leafs)
	{
		if(leaf != begin)
		{
			Node* track = leaf;
			std::vector<Node*> singleTrack;
			//going back to the starting node
			while(track != mapOfAncedents[track])
			{
				singleTrack.push_back(track);
				track = mapOfAncedents[track];
			}
			//last one
			singleTrack.push_back(track);

			//add new track to the rest
			vectorOfTracks.push_back(singleTrack);
		}
	}
}

void Tree::printTheWholePath(std::vector<Node*>& v)
{
	for(Node* node : v)
		printf("%d ", node->getID());
	printf("\n");
}

void Tree::setMarkedForAll(std::vector<Node*>& v)
{
	for(Node* node : v)
		node->setMarked(true);
}

int Tree::getCoverage()
{
	int coverage = 0;
	for(auto& node : this->mapOfNodes)
		if(node.second->isMarked())
			coverage++;

	return coverage;
}