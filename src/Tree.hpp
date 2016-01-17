#include <map>
#include <queue>

class Tree
{
private:
	std::map<int, Node*> mapOfNodes;

public:

	Tree(){}

	~Tree()
	{
		this->mapOfNodes.clear();
	}

	Node* getNode(int ID)
	{
		if(mapOfNodes[ID] == NULL)
			mapOfNodes[ID] = new Node(ID);

		return mapOfNodes[ID];
	}

	void BFS()
	{
		std::queue<Node*> q;
		std::map<Node*, bool> visited;

		for(auto& root : mapOfNodes)
		{
			if(visited[root.second] == false)
			{
				q.push(root.second);
				visited[root.second] = true;

				while(!q.empty())
				{
					Node* temp = q.front();
					q.pop();
					std::cout << temp->getID() << std::endl;

					for(Node* node : temp->getNeighbours())
					{
						if(visited[node] == false)
						{
							q.push(node);
							visited[node] = true; 
						}
					}

				}
			}
		}
	}
};