#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"


struct AABB {
	glm::vec3 min;
	glm::vec3 max;

	AABB(const glm::vec3 &minVal, const glm::vec3 &maxVal)
	{
		min = minVal;
		max = maxVal;
	}
	AABB()
	{
		min = glm::vec3(0.0f);
		max = glm::vec3(0.0f);
	}
};

/// <summary>
/// Represents one 'renderable' objet
/// </summary>
class GameEntity
{
private:
    Mesh* mesh;        
    Material* material;

    //TODO - maybe this should be in a transform class?
    
    glm::vec3 eulerAngles;
    glm::vec3 scale;
    
    glm::mat4 worldMatrix;

	//physics stuff
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 startPos;
	

	bool gravity;

public: 
    /// <summary>
    /// Basic paramterized constructor for most of our private vars
    /// </summary>
    GameEntity(
        Mesh* mesh,
        Material* material,
        glm::vec3 position,
        glm::vec3 eulerAngles,
        glm::vec3 scale
    );

    /// <summary>
    /// Destruction
    /// </summary>
    virtual ~GameEntity();

    /// <summary>
    /// Updates the worldMatrix
    /// </summary>
    virtual void Update(float dt);

    /// <summary>
    /// Renders the gameEntity based on a camera
    /// </summary>
    void Render(Camera* camera);

	bool activated;
	
	void AddPosition(glm::vec3 pos);
	glm::vec3 GetPos() {
		return position;
	}
	void AddVelocity(glm::vec3 vel);
	void SetVelocity(glm::vec3 vel);
	glm::vec3 GetVelocity()
	{
		return velocity;
	}
	void AddAcceleration(glm::vec3 acc);
	void SetAcceleration(glm::vec3 acc);
	void ToggleGravity();

	AABB box;
	void CalculateBox();
	std::vector<glm::vec3> GetPoints();
	std::vector<glm::vec3> GetNormals();
	void GetMinMax(glm::vec3 axis, float& min, float& max);

	float mass;
	void SetMass(float mass);

	bool enabled;
	bool orbital;

	void AddScale(glm::vec3 scale);
	void SetScale(glm::vec3 scale);
	glm::vec3 GetScale() {
		return scale;
	}

	glm::vec3 startVel;

	void Reset();

};

