#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
}

void Mesh::InitWithVertexArray(GLfloat vertices[], size_t count, GLuint shaderProgram)
{
	//allocate space for all these vertices
	this->vertices = std::vector<GLfloat>(count);
	memcpy(&(this->vertices[0]), vertices, count * sizeof(GLfloat));

	//vertCount is how many vertices we have
	//since 3 floats make up one vertices, we divide by 3
	//(yeah this is bad, and you should feel disgusted)
	vertCount = count / 3;

	//we create the VAO and VBO based off of all these data
	CreateBuffers(shaderProgram);
}

void Mesh::Render()
{
	//set VAO and draw
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertCount);
}

void Mesh::CreateBuffers(GLuint shaderProgram)
{
	glGenVertexArrays(1, &VAO);	//create 1 VAO and store it
	glBindVertexArray(VAO);		//tells OpenGL that this is our 'array' (descriptor)

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//tells OpenGL that this is our 'array buffer' (memory)
	glBufferData(			//create a 'buffer store' (place to put this memory in GPU)						
		GL_ARRAY_BUFFER,
		sizeof(GLfloat) * 3 * vertCount,	//the size of our buffer
		&(vertices[0]),		                //pointer to starting loc
		GL_STATIC_DRAW);	                //'hints' at what this will be used for

	//GL_ARRAY_BUFFER msut be bound prior to this call
	GLuint attribIndex = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(
		attribIndex,			//index of attribute
		3,						//count of data (this case we have a vec3 -- which has 3 floats)
		GL_FLOAT,				//kind of data (as mentioned, this is a float!)
		GL_FALSE,				//should data be normalized?
		6 * sizeof(GLfloat),	//stride - how many index to skip ahead to reach more of this data
		(GLvoid*)0);			//offset - how many index to skip to reach first value
	glEnableVertexAttribArray(attribIndex);	//enable what we just did earlier 

	GLuint normalIndex = glGetAttribLocation(shaderProgram, "aNormal");
	glVertexAttribPointer(
		normalIndex,			//index of attribute
		3,						//count of data (this case we have a vec3 -- which has 3 floats)
		GL_FLOAT,				//kind of data (as mentioned, this is a float!)
		GL_FALSE,				//should data be normalized?
		6 * sizeof(GLfloat),	//stride - how many index to skip ahead to reach more of this data
		(GLvoid*)0);			//offset - how many index to skip to reach first value
	glEnableVertexAttribArray(normalIndex);

	//unbind things
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
