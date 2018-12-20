#pragma once
#include <vector>
#include "Node.h"
#include "GameEntity.h"
#include <irrKlang.h>
using namespace irrklang;

class KDTree
{
private:
	vector<Node*> tree;

public:
	KDTree();
	~KDTree();

	void PutInTree(GameEntity* obj);
	void ClearObjsInTree();
	void UpdateTree(vector<GameEntity*> objs, int numObjs);
	bool CheckIfSameSpace(GameEntity* obj1, GameEntity* obj2);
	void CheckCollisions(vector<GameEntity*> objs, int numObjs);
	GameEntity* center;

	bool SAT(GameEntity a, GameEntity b);

	ISoundEngine *explosion = createIrrKlangDevice();
};

