#pragma once
#include "stdafx.h"
#include "Camera.h"

/// <summary>
/// Represents one material to apply to a renderable item, and handles sending 
/// any uniform over from CPU to GPU.
/// </summary>
class Material
{
private:
	//TODO: if you have additional textures to bind, it will go here
	
	//handle to the shader program
	GLuint shaderProgram;
	glm::vec3 colorLght;
	glm::vec3 colorObj;
	glm::vec3 lightPosition;
	glm::vec3 cameraPosition;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	
	float shininess;
	
	
	
public:

	/// <summary>
	/// Creates a 'material' for a certain shaderProgram
	/// </summary>
	/// <param name="shaderProgram"></param>
	Material(GLuint shaderProgram, glm::vec3 colorL, glm::vec3 colorO);
	Material(GLuint shaderProgram, glm::vec3 colorL, glm::vec3 colorO, glm::vec3 lightPos, glm::vec3 cameraPos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shin);

	/// <summary>
	/// Destruction
	/// </summary>
	~Material();

	/// <summary>
	/// Binds the data that's needed to the uniforms
	/// </summary>
	/// <param name="camera">Pointer to the rendering camera</param>
	/// <param name="worldMatrix">Matrix from model to world space</param>
	void Bind(
		Camera* camera,
		glm::mat4 worldMatrix
	);
};


