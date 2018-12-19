#include "GameEntity.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <glm/gtc/quaternion.hpp>

GameEntity::GameEntity(Mesh * mesh, 
    Material * material,
    glm::vec3 position, 
    glm::vec3 eulerAngles, 
    glm::vec3 scale)
{
    this->mesh = mesh;
    this->material = material;
    this->position = position;
    this->eulerAngles = eulerAngles;
    this->scale = scale;
    worldMatrix = glm::identity<glm::mat4>();
	activated = false;
	gravity = false;
	mass = 1.0f;
	enabled = true;
	orbital = true;
	startPos = position;
	startQuat = glm::quat(eulerAngles);
	rotQuat = glm::quat(glm::vec3(0, 180, 0));
}

GameEntity::~GameEntity()
{
}

void GameEntity::Update(float dt)
{
	if (enabled) {
		if (gravity) {
			acceleration = glm::vec3(0.0f, -4.6f, 0.0f);
		}
		velocity += acceleration * dt;
		position += velocity * dt;

		worldMatrix = glm::identity<glm::mat4>();
		worldMatrix = glm::translate(worldMatrix, position);
		if (!orbital) {
			//eulerAngles.y += .01;
			//worldMatrix = glm::rotate(worldMatrix, eulerAngles.y, glm::vec3(0.f, 1.f, 0.f));

			timer += .01f;
			glm::quat interQuat = glm::mix(startQuat, rotQuat, timer);
			glm::mat4 rotMatrix = glm::mat4_cast(interQuat);
			worldMatrix = worldMatrix * rotMatrix;

			//glm::vec3 tempEuler = eulerAngles;
			//tempEuler.y += 180;
			
			//worldMatrix = glm::mix(worldMatrix, glm::rotate(worldMatrix, tempEuler.y, glm::vec3(0.f, 1.f, 0.f)), timer);
		}
		worldMatrix = glm::scale(worldMatrix, scale);
	}
}

void GameEntity::Render(Camera* camera)
{
	if (enabled) {
		material->Bind(camera, worldMatrix);
		mesh->Render();
	}
}

void GameEntity::AddPosition(glm::vec3 pos)
{
	position += pos;
}

void GameEntity::AddVelocity(glm::vec3 vel)
{
	velocity += vel;
}

void GameEntity::SetVelocity(glm::vec3 vel)
{
	velocity = vel;
}

void GameEntity::AddAcceleration(glm::vec3 acc)
{
	acceleration += acc;
}

void GameEntity::SetAcceleration(glm::vec3 acc)
{
	acceleration = acc;
}

void GameEntity::ToggleGravity()
{
	gravity = !gravity;
}

void GameEntity::CalculateBox()
{
	AABB newBox;

	newBox.min = position;
	newBox.max = newBox.min;

	for (size_t i = 0; i < mesh->vertCount; i++)
	{
		glm::vec3 tempVert = glm::vec3(position.x + mesh->vertices[i], position.y + mesh->vertices[i + 1], position.z + mesh->vertices[i + 2]);

		if (tempVert.x > newBox.max.x)
		{
			newBox.max.x = tempVert.x;
		}
		if (tempVert.y > newBox.max.y)
		{
			newBox.max.y = tempVert.y;
		}
		if (tempVert.z > newBox.max.z)
		{
			newBox.max.z = tempVert.z;
		}

		if (tempVert.x < newBox.min.x)
		{
			newBox.min.x = tempVert.x;
		}
		if (tempVert.y < newBox.min.y)
		{
			newBox.min.y = tempVert.y;
		}
		if (tempVert.z < newBox.min.z)
		{
			newBox.min.z = tempVert.z;
		}
	}

	box.min.x = newBox.min.x;
	box.min.y = newBox.min.y;
	box.min.z = newBox.min.z;
	box.max.x = newBox.max.x;
	box.max.y = newBox.max.y;
	box.max.z = newBox.max.z;
}

std::vector<glm::vec3> GameEntity::GetPoints()
{
	std::vector<glm::vec3> points;

	points.push_back(glm::vec3(box.min.x, box.min.y, box.min.z));
	points.push_back(glm::vec3(box.min.x, box.max.y, box.min.z));
	points.push_back(glm::vec3(box.min.x, box.max.y, box.max.z));
	points.push_back(glm::vec3(box.min.x, box.min.y, box.max.z));

	points.push_back(glm::vec3(box.max.x, box.max.y, box.max.z));
	points.push_back(glm::vec3(box.max.x, box.max.y, box.min.z));
	points.push_back(glm::vec3(box.max.x, box.min.y, box.min.z));
	points.push_back(glm::vec3(box.max.x, box.min.y, box.max.z));

	return points;
}

std::vector<glm::vec3> GameEntity::GetNormals()
{
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> points = GetPoints();

	glm::vec3 U(points[1] - points[0]);
	glm::vec3 V(points[2] - points[0]);

	normals.push_back(glm::normalize(glm::vec3((U.y * V.z) - (U.z * V.y), (U.z * V.x) - (U.x * V.z), (U.x * V.y) - (U.y * V.x))));

	glm::vec3 U1(points[5] - points[4]);
	glm::vec3 V1(points[2] - points[4]);

	normals.push_back(glm::normalize(glm::vec3((U1.y * V1.z) - (U1.z * V1.y), (U1.z * V1.x) - (U1.x * V1.z), (U1.x * V1.y) - (U1.y * V1.x))));

	glm::vec3 U2(points[1] - points[0]);
	glm::vec3 V2(points[5] - points[0]);

	normals.push_back(glm::normalize(glm::vec3((U2.y * V2.z) - (U2.z * V2.y), (U2.z * V2.x) - (U2.x * V2.z), (U2.x * V2.y) - (U2.y * V2.x))));

	return normals;
}

void GameEntity::GetMinMax(glm::vec3 axis, float & min, float & max)
{
	std::vector<glm::vec3> points = GetPoints();

	min = glm::dot(points[0], axis);
	max = min;

	for (int i = 1; i < points.size(); i++)
	{
		float currProj = glm::dot(points[i], axis);

		if (min > currProj)
		{
			min = currProj;
		}

		if (currProj > max)
		{
			max = currProj;
		}
	}
}

void GameEntity::SetMass(float mass)
{
	this->mass = mass;
}

void GameEntity::AddScale(glm::vec3 scale)
{
	this->scale += scale;
}

void GameEntity::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}

void GameEntity::Reset()
{
	position = startPos;
	velocity = startVel;
	enabled = true;
}
