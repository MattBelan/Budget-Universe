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
	explosion->drop();
}

//Puts specified object as a leaf of one of the nodes of the tree
//tree changes depending on the position of the center planet
void KDTree::PutInTree(GameEntity * obj)
{
	glm::vec3 pos = obj->GetPos();
	if (glm::dot(pos, glm::vec3(1.0f, 0, 0)+center->GetPos()) > 0) {
		if (glm::dot(pos, glm::vec3(0, 1.0f, 0) + center->GetPos()) > 0) {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f) + center->GetPos()) > 0) {
				tree[3]->AddObj(obj);
				return;
			}
			else {
				tree[4]->AddObj(obj);
				return;
			}
		}
		else {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f) + center->GetPos()) > 0) {
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
		if (glm::dot(pos, glm::vec3(0, 1.0f, 0) + center->GetPos()) > 0) {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f) + center->GetPos()) > 0) {
				tree[10]->AddObj(obj);
				return;
			}
			else {
				tree[11]->AddObj(obj);
				return;
			}
		}
		else {
			if (glm::dot(pos, glm::vec3(0, 0, 1.0f) + center->GetPos()) > 0) {
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

//Clears all objects from the tree
void KDTree::ClearObjsInTree()
{
	for (size_t i = 0; i < 14; i++)
	{
		tree[i]->ClearObjs();
	}
}

//Clears the tree and places all active objects in the tree
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

//checks if two objects are in the same node
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

//checks each node's objects against each other to see if there are collisions
///on a collision, momentum between the objects is preserved, and the larger of the objects grows in scale
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

							explosion->setSoundVolume(.3f);
							explosion->play2D("assets/Audio/explosion.mp3", GL_FALSE);
						}
					}

				}
			}
		}
	}
	
}

//checks to see if there are any collisions
bool KDTree::SAT(GameEntity a, GameEntity b)
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
