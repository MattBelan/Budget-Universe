#pragma once
#include <vector>
#include "Node.h"
#include "GameEntity.h"

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

	bool SAT(GameEntity a, GameEntity b)
	{
		std::vector<glm::vec3> aNormals = a.GetNormals();
		std::vector<glm::vec3> bNormals = b.GetNormals();

		bool notColliding = false;

		for (int i = 0; i < aNormals.size(); i++)
		{
			float aMin, aMax;
			a.GetMinMax(aNormals[i], aMin, aMax);

			float bMin, bMax;
			b.GetMinMax(aNormals[i], bMin, bMax);

			notColliding = aMax < bMin || bMax < aMin;
			if (notColliding) break;
		}

		if (!notColliding)
		{
			for (int i = 0; i < bNormals.size(); i++)
			{
				float aMin, aMax;
				a.GetMinMax(bNormals[i], aMin, aMax);

				float bMin, bMax;
				b.GetMinMax(bNormals[i], bMin, bMax);

				notColliding = aMax < bMin || bMax < aMin;
				if (notColliding) break;
			}
		}

		return !notColliding;
	}
};

