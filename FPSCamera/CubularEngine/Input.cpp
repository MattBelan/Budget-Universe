#include "Input.h"

//for singleton
Input* Input::instance = nullptr;

Input::Input()
{
}

Input::~Input()
{
}

Input* Input::GetInstance()
{
    //basic singleton stuff

    if (instance == nullptr)
    {
        instance = new Input();
    }
    return instance;
}

void Input::Release()
{
    //TODO - check if instance is instance is a nullptr?
    delete instance;
    instance = nullptr;
}

void Input::Init(GLFWwindow * window)
{
    //TODO - honestly this feels pretty weird that a singleton will require
    //       an Init before it works. Some people wouldn't consider this a 
    //       true singleton. (Maybe it shouldn't ba singleton?)
    this->window = window;
}

bool Input::IsKeyDown(int key)  
{
    //TODO - maybe we should assert if window is nullptr
    return glfwGetKey(window, key) == GLFW_PRESS;
}
