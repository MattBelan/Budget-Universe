#include "Shader.h"

Shader::Shader()
{
	//do nothing
}

Shader::~Shader()
{
	glDeleteShader(shaderLoc);
}

bool Shader::InitFromFile(std::string filePath, GLenum shaderType)
{
	std::ifstream file(filePath);

	// Check if the file exists
	if (!file.good())
	{
#ifdef _DEBUG
		// If we encounter an error, print a message and return false.
		std::cout << "Can't read file: " << filePath << std::endl;
#endif
		return false;
	}

	// ifstream internally keeps track of where in the file.

	// Here we find the end of the file.
	file.seekg(0, std::ios::end);

	// Make a string and set its size equal to the length of the file.
	std::string shaderCode;
	shaderCode.resize((size_t)file.tellg());

	// Go back to the beginning of the file.
	file.seekg(0, std::ios::beg);

	// Read the file into the string until we reach the end of the string.
	file.read(&shaderCode[0], shaderCode.size());

	// Close the file.
	file.close();

	// Init using the string.
	return InitFromString(shaderCode, shaderType);
}

bool Shader::InitFromString(std::string shaderCode, GLenum shaderType)
{
	// Get the char* and length
	const char* shaderCodePointer = shaderCode.data();
	int shaderCodeLength = shaderCode.size();

	shaderLoc = glCreateShader(shaderType);

	// Set the source code and compile.
	glShaderSource(shaderLoc, 1, &shaderCodePointer, &shaderCodeLength);
	glCompileShader(shaderLoc);

	GLint isCompiled;

	// Check if the fragmentShader compiles:
	// If it failed, print an error and delete it.
	glGetShaderiv(shaderLoc, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
	{
		char infolog[1024];
		glGetShaderInfoLog(shaderLoc, 1024, NULL, infolog);
#ifdef _DEBUG
		std::cout << "Shader compile failed with error: " << std::endl << infolog << std::endl;
#endif

		// Delete the shader, and set the index to zero so that this object knows it doesn't have a shader.
		glDeleteShader(shaderLoc);
		shaderLoc = 0;
		return false;
	}
	else
	{
		return true;
	}
}

