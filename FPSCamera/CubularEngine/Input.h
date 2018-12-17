#pragma once
#include "stdafx.h"

/// <summary>
/// Singleton that does basic input handling
/// </summary>

//TODO - refactor a few things for this class to handle 'isKeyPressed' or
//       'isKeyReleased'.

//TODO - refactor a few things for this class to handle mouse input

//(maybe consider a callback pattern instead?)

class Input
{
private:      
    /// <summary>
    /// Singleton implementation (private constructor & destructor)
    /// </summary>
    Input();
    ~Input();

    static Input* instance;     //singleton stuff
    
public:
    /// <summary>
    /// Singleton reference to the instance
    /// </summary>
    static Input* GetInstance();

    /// <summary>
    /// De-allocation
    /// </summary>
    static void Release();

    /// <summary>
    /// Initializes the input singleton before input can be detected properly
    /// </summary>
    void Init(GLFWwindow* window);

    /// <summary>
    /// Checks if the key is down
    /// </summary>
    bool IsKeyDown(int key);

	GLFWwindow* window;         //window (required for input)
};

