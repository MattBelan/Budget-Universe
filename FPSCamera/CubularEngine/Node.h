#pragma once
#include <vector>
#include "GameEntity.h"
using namespace std;

class Node
{
private:
	vector<Node*> nodes;
	vector<GameEntity*> objects;
	int numNodes;
	
public:
	Node();
	~Node();

	int numObjs;

	void RemoveNode(Node *obj);
	void AddNode(Node *obj);

	vector<Node*> GetNodes() {
		return nodes;
	}

	void AddObj(GameEntity *obj);
	void RemoveObj(GameEntity *obj);
	void ClearObjs();

	vector<GameEntity*> GetObjects() {
		return objects;
	}
	int GetNumObjs() {
		return numObjs;
	}
};

