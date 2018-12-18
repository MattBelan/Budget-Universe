#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"

Camera::Camera(glm::vec3 position,
    glm::vec3 forward, 
    glm::vec3 up, 
    float fovAngleY, 
    float width, 
    float height,
    float nearZ, 
    float farZ)
{
    this->position = position;
    this->forward = forward; 
    this->up = up;

    //does this calculation once
    this->fov = fovAngleY * glm::pi<float>() / 180.0f;
    this->width = width;
    this->height = height;
    this->nearZ = nearZ;
    this->farZ = farZ;

	this->lastX = 400;
	this->lastY = 300;
	this->yaw = 90.0f;
	this->pitch = 0.0f;

	this->firstMouse = true;

	startForward = forward;
	startUp = up;
	startPos = position;
}

Camera::~Camera()
{
}

//TODO - incorporate deltaTime
//TODO - maybe separate this function should instead call two private functions
//       (something like UpdateInput() and UpdateMatrices())
void Camera::Update()
{
	//Setting Right Vector
	SetRight();

    //TODO - cache the pointer to the Input single instance instead of calling 
    //       GetInstance() multiple times
    if (Input::GetInstance()->IsKeyDown(GLFW_KEY_A))
    {
        //TODO - change this to move along local axes instead of global axes
		position += right;
    } 
     
    //TODO - cache the pointer to the Input single instance instead of calling 
    //       GetInstance() multiple times
    else if (Input::GetInstance()->IsKeyDown(GLFW_KEY_D))
    {
        //TODO - change this to move along local axes instead of global axes
		position -= right;
    } 

	//forward/backward
	if (Input::GetInstance()->IsKeyDown(GLFW_KEY_W)) {
		position += forward;
	}

	else if (Input::GetInstance()->IsKeyDown(GLFW_KEY_S)) {
		position -= forward;
	}

	//up/down
	if (Input::GetInstance()->IsKeyDown(GLFW_KEY_E)) {
		position += up;
	}

	else if (Input::GetInstance()->IsKeyDown(GLFW_KEY_Q)) {
		position -= up;
	}


    //this call may not be needed every frame
    forward = glm::normalize<3>(forward);   

    //view matrix
    //we use forward here instead of a lookTarget because it's easier to track
    //and conceptualize.
    viewMatrix = glm::lookAtLH(
        position,               //where the camera is
        position + forward,     //where the camera is looking at 
        up                      //what is 'up' for the camera
    );

    //create the projection matrix
    projectionMatrix = glm::perspectiveFovLH<GLfloat>(
        fov,
        width,                  //the width of the window in float
        height,                 //the height of the window in float
        nearZ,                  //the near Z-plane
        farZ                    //the far Z-plane
    );
}

void Camera::SetRight()
{
	right = glm::cross(forward, up);
}

void Camera::UpdateRotation(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw -= xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(front);
}

void Camera::Reset()
{
	position = startPos;
	forward = startForward;
	up = startUp;
}
