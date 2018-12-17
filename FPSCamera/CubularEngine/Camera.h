#pragma once
#include "stdafx.h"

class Camera
{
private:
         //position of camera
    glm::vec3 up;           //what 'up' is for the camera
	glm::vec3 right;

    float fov;      //field of view
    float width;    //width of screen
    float height;   //height of screen
    float nearZ;    //near Z-plane
    float farZ;     //far  Z-plane

    
	float pitch;
	float yaw;
	float lastX;
	float lastY;

	bool firstMouse;

public:

    /// <summary>
    /// Constructor where you supply everything you need for the 2 matrices
    /// </summary>
    Camera(
        glm::vec3 position,
        glm::vec3 forward,
        glm::vec3 up,
        float fovAngleY,
        float width,
        float height,
        float nearZ,
        float farZ  
    );

    /// <summary>
    /// Destruction
    /// </summary>
    ~Camera();

    /// <summary>
    /// Queries input and updates the matrices of the camera
    /// </summary>
    void Update();

    /// <summary>
    /// Gets the view matrix
    /// </summary>
    glm::mat4 GetView() const { return viewMatrix; }
    
    /// <summary>
    /// Gets the projection matrix
    /// </summary>
    glm::mat4 GetProjection() const { return projectionMatrix; }

	void SetRight();

	glm::vec3 forward;
	glm::mat4 viewMatrix;       //cached view matrix
	glm::mat4 projectionMatrix; //cached projection matrix
	glm::vec3 position;

	void UpdateRotation(double xpos, double ypos);

	glm::vec3 GetPos() {
		return position;
	}
    //TODO - maybe having getters & setters for other private variables would be
    //useful for you
};

