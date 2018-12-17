#include "Node.h"



Node::Node()
{
	numNodes = 0;
	numObjs = 0;
}


Node::~Node()
{
}

void Node::RemoveNode(Node *obj)
{
	if (numNodes > 0) {
		vector<Node*> tempNodes;
		for (size_t i = 0; i < numNodes; i++)
		{
			if (nodes[i] != obj) {
				tempNodes.push_back(nodes[i]);
			}
		}
		nodes = tempNodes;
		numNodes--;
	}
}

void Node::AddNode(Node *obj)
{
	numNodes++;
	nodes.push_back(obj);
}

void Node::RemoveObj(GameEntity * obj)
{
	if (numObjs > 0) {
		vector<GameEntity*> tempObjs;
		for (size_t i = 0; i < numObjs; i++)
		{
			if (objects[i] != obj) {
				tempObjs.push_back(objects[i]);
			}
		}
		objects = tempObjs;
		numObjs--;
	}
}

void Node::AddObj(GameEntity * obj)
{
	numObjs++;
	objects.push_back(obj);
}

void Node::ClearObjs()
{
	objects.clear();
	numObjs = 0;
}
