#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

class Node
{
public:
	Node(int id) : id(id) {}

	void AddAdjacentNode(Node *node)
	{
		adjNodes.push_back(node);
	}

	void SetIsRootNode(bool val)
	{
		isRootNode = val;
	}

	bool IsRootNode()
	{
		return isRootNode;
	}

	int MaxDescendants()
	{
		int max = -1;
		for (int i = 0; i < adjNodes.size(); i++)
		{
			int desc = adjNodes[i]->MaxDescendants();
			max = max < desc ? desc : max;
		}
		return max + 1;
	}

private:
	int id;
	bool isRootNode = true;
	vector<Node*> adjNodes;
};

class Graph
{
public:
	~Graph()
	{
		for (auto it = nodes.begin(); it != nodes.end(); it++)
		{
			delete it->second;
		}
	}

	void AddEdge(int idFrom, int idTo)
	{
		Node *from = GetNode(idFrom);
		Node *to = GetNode(idTo);
		from->AddAdjacentNode(to);
		to->SetIsRootNode(false);
	}

	vector<Node*> GetRootNodes()
	{
		vector<Node*> rootNodes;

		for (auto it = nodes.begin(); it != nodes.end(); it++)
		{
			if (it->second->IsRootNode())
			{
				rootNodes.push_back(it->second);
			}
		}

		return rootNodes;
	}

	int MaxPathLength()
	{
		int max = -1;
		vector<Node*> rootNodes = GetRootNodes();

		for (int i = 0; i < rootNodes.size(); i++)
		{
			int desc = rootNodes[i]->MaxDescendants();
			max = max < desc ? desc : max;
		}

		return max + 1;
	}

private:
	unordered_map<int, Node*> nodes;

	Node *GetNode(int id)
	{
		if (nodes.count(id))
		{
			return nodes[id];
		}

		Node *node = new Node(id);
		nodes[id] = node;
		return node;
	}
};

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
int main()
{
	Graph graph;

	int n; // the number of relationships of influence
	cin >> n; cin.ignore();
	for (int i = 0; i < n; i++) {
		int x; // a relationship of influence between two people (x influences y)
		int y;
		cin >> x >> y; cin.ignore();

		graph.AddEdge(x, y);
	}

	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

	cout << graph.MaxPathLength() << endl; // The number of people involved in the longest succession of influences
}