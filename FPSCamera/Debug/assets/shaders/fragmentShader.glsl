/*
This is the fragment shader, and it's main job is to determine the color for each pixel (fragment)
*/

//specifies the version of the shader (and what features are enabled)
#version 400 core

out vec4 color;

//entry point for the fragment shader
void main(void)
{
	// sets the output (color) to red
	color = vec4(1, 1, 1, 1);
	
}