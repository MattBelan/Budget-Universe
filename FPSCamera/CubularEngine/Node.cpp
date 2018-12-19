#include "Node.h"



Node::Node()
{
	numNodes = 0;
	numObjs = 0;
}


Node::~Node()
{
}

//removes the desired node from this nodes branches
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

//adds a node to this node's branches
void Node::AddNode(Node *obj)
{
	numNodes++;
	nodes.push_back(obj);
}

//removes the desired object from this node
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

//adds the object to this node
void Node::AddObj(GameEntity * obj)
{
	numObjs++;
	objects.push_back(obj);
}

//clears all objetcs from this node
void Node::ClearObjs()
{
	objects.clear();
	numObjs = 0;
}
