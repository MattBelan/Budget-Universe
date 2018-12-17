#include "KDTree.h"
#include <iostream>



KDTree::KDTree()
{
	for (size_t i = 0; i < 14; i++)
	{
		tree.push_back(new Node());
	}

	//setting up tree
	//tree[0] is our pos x node
	tree[0]->AddNode(tree[1]);//pos y of pos x
	tree[0]->AddNode(tree[2]);//neg y of pos x
	tree[1]->AddNode(tree[3]);//posz of pos y of pos x
	tree[1]->AddNode(tree[4]);//negz of posy of posx
	tree[2]->AddNode(tree[5]);//posz of negy of posx
	tree[2]->AddNode(tree[6]);//negz of negy of posx
	//tree[7] is our neg x node
	tree[7]->AddNode(tree[8]);//posy of neg x
	tree[7]->AddNode(tree[9]);//negy of negx
	tree[8]->AddNode(tree[10]);//posz of posy of negx
	tree[8]->AddNode(tree[11]);//negz of posy of negx
	tree[9]->AddNode(tree[12]);//posz of negy of negx
	tree[9]->AddNode(tree[13]);//negz of negy of negx
}


KDTree::~KDTree()
{
	for (size_t i = 0; i < 14; i++)
	{
		delete tree[i];
	}
}

void KDTree::PutInTree(GameEntity * obj)
{
	glm::vec3 pos = obj->GetPos();
	if (glm::dot(pos, glm::vec3(1.0f, 0, 0)) > 0) {
		if (glm::dot(pos, glm::vec3(0, 1.0f, 0)) > 0) {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f)) > 0) {
				tree[3]->AddObj(obj);
				return;
			}
			else {
				tree[4]->AddObj(obj);
				return;
			}
		}
		else {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f)) > 0) {
				tree[5]->AddObj(obj);
				return;
			}
			else {
				tree[6]->AddObj(obj);
				return;
			}
		}
	}
	else {
		if (glm::dot(pos, glm::vec3(0, 1.0f, 0)) > 0) {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f)) > 0) {
				tree[10]->AddObj(obj);
				return;
			}
			else {
				tree[11]->AddObj(obj);
				return;
			}
		}
		else {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f)) > 0) {
				tree[12]->AddObj(obj);
				return;
			}
			else {
				tree[13]->AddObj(obj);
				return;
			}
		}
	}
}

void KDTree::ClearObjsInTree()
{
	for (size_t i = 0; i < 14; i++)
	{
		tree[i]->ClearObjs();
	}
}

void KDTree::UpdateTree(vector<GameEntity*> objs, int numObjs)
{
	ClearObjsInTree();
	for (size_t i = 0; i < numObjs; i++)
	{
		if (objs[i]->enabled) {
			PutInTree(objs[i]);
		}
	}
}

bool KDTree::CheckIfSameSpace(GameEntity * obj1, GameEntity * obj2)
{
	vector<GameEntity*> nodeObjs;
	int numObjs = 0;
	for (size_t i = 0; i < 14; i++)
	{
		nodeObjs = tree[i]->GetObjects();
		numObjs = tree[i]->GetNumObjs();
		bool obj1Here = false;
		bool obj2Here = false;
		if (numObjs > 0) {
			for (size_t i = 0; i < numObjs; i++)
			{
				if (nodeObjs[i] == obj1) {
					obj1Here = true;
				}
				if (nodeObjs[i] == obj2) {
					obj2Here = true;
				}
			}
		}
		if (obj1Here && obj2Here) {
			return true;
		}
	}
	return false;
}

void KDTree::CheckCollisions(vector<GameEntity*> objs, int numTotalObjs)
{
	vector<GameEntity*> nodeObjs;
	int numObjs = 0;
	for (size_t i = 0; i < 14; i++)
	{
		nodeObjs = tree[i]->GetObjects();
		numObjs = tree[i]->numObjs;
		if (numObjs > 0) {
			
			for (size_t i = 0; i < numObjs; i++)
			{
				for (size_t j = 0; j < numObjs; j++)
				{
					if (i != j) {

						if (SAT(*nodeObjs[i], *nodeObjs[j])) {

							if (nodeObjs[i]->orbital) {
								float newMass = nodeObjs[i]->mass + nodeObjs[j]->mass;
								glm::vec3 newVel = (nodeObjs[i]->mass*nodeObjs[i]->GetVelocity() + nodeObjs[j]->mass*nodeObjs[j]->GetVelocity()) / newMass;

								nodeObjs[j]->SetMass(newMass);
								nodeObjs[j]->SetVelocity(newVel);
								if (nodeObjs[i]->GetScale().x > nodeObjs[j]->GetScale().x) {
									nodeObjs[j]->SetScale(nodeObjs[i]->GetScale());
								}
								nodeObjs[j]->AddScale(nodeObjs[i]->GetScale() / 4.f);

								nodeObjs[i]->AddPosition(glm::vec3(1000.f, 1000.f, 1000.f));
								nodeObjs[i]->enabled = false;
							}
							else {
								float newMass = nodeObjs[i]->mass + nodeObjs[j]->mass;
								glm::vec3 newVel = (nodeObjs[i]->mass*nodeObjs[i]->GetVelocity() + nodeObjs[j]->mass*nodeObjs[j]->GetVelocity()) / newMass;

								nodeObjs[i]->SetMass(newMass);
								nodeObjs[i]->SetVelocity(newVel);
								if (nodeObjs[j]->GetScale().x > nodeObjs[i]->GetScale().x) {
									nodeObjs[i]->SetScale(nodeObjs[j]->GetScale());
								}
								nodeObjs[i]->AddScale(nodeObjs[j]->GetScale()/4.f);

								nodeObjs[j]->AddPosition(glm::vec3(1000.f, 1000.f, 1000.f));
								nodeObjs[j]->enabled = false;
							}
							UpdateTree(objs, numTotalObjs);
							nodeObjs = tree[i]->GetObjects();
							numObjs = tree[i]->numObjs;

						}
					}

				}
			}
		}
	}
	
}
