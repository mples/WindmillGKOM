#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <iostream>
#include "WallsModel.h"

static GLfloat wallsMesh[] = {

	//front
		-0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 1.0f, 1.0f,
		0.5f,  0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 1.0f, 0.0f,
		0.5f,  0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 1.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 0.0f, 1.0f,

	//back
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,		 1.0f, 1.0f,
		0.5f,  -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,			0.0f, 0.0f, -1.0f,		 1.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,		 0.0f, 1.0f,

	//right
		0.5f, 0.5f, 0.5f,			1.0f, 0.0f, 0.0f,		 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,			1.0f, 0.0f, 0.0f,		 0.0f, 0.0f,
		0.5f,  -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		 1.0f, 0.0f,
		0.5f,  0.5f, 0.5f,			1.0f, 0.0f, 0.0f,		 0.0f, 1.0f,
		0.5f,  -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,			1.0f, 0.0f, 0.0f,		 1.0f, 1.0f,

	//left
		-0.5f, 0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,		 1.0f, 1.0f,
		-0.5f,  -0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,		 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,		 1.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,		 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,			-1.0f, 0.0f, 0.0f,		 0.0f, 1.0f,
		-0.5f,  -0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,		 0.0f, 0.0f,
};

WallsModel::WallsModel(GLfloat size, glm::vec3 color)
{

	for (int i = 0; i < _countof(wallsMesh) / 8; ++i)
	{
		wallsCoord.push_back(wallsMesh[i * 8] * size);
		wallsCoord.push_back(wallsMesh[i * 8 + 1] * size);
		wallsCoord.push_back(wallsMesh[i * 8 + 2] * size);
		wallsCoord.push_back(color.x);
		wallsCoord.push_back(color.y);
		wallsCoord.push_back(color.z);
		wallsCoord.push_back(wallsMesh[i * 8 + 3] );
		wallsCoord.push_back(wallsMesh[i * 8 + 4]);
		wallsCoord.push_back(wallsMesh[i * 8 + 5]);
		wallsCoord.push_back(wallsMesh[i * 8 + 6]);
		wallsCoord.push_back(wallsMesh[i * 8 + 7]);
	}
	for (int i = 0; i < _countof(wallsMesh) / 8; ++i)
	{
		wallsCoord.push_back(wallsMesh[i * 8] * size * 0.9f);
		wallsCoord.push_back(wallsMesh[i * 8 + 1] * size);
		wallsCoord.push_back(wallsMesh[i * 8 + 2] * size * 0.9f);
		wallsCoord.push_back(color.x);
		wallsCoord.push_back(color.y);
		wallsCoord.push_back(color.z);
		wallsCoord.push_back(wallsMesh[i * 8 + 3] * -1.0f);
		wallsCoord.push_back(wallsMesh[i * 8 + 4] * -1.0f);
		wallsCoord.push_back(wallsMesh[i * 8 + 5] * -1.0f);
		wallsCoord.push_back(wallsMesh[i * 8 + 6]);
		wallsCoord.push_back(wallsMesh[i * 8 + 7]);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * wallsCoord.size(), &(wallsCoord[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


WallsModel::~WallsModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void WallsModel::draw(const glm::mat4 & modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)wallsCoord.size());

	glBindVertexArray(0);
}

void WallsModel::setTexture(const char * texName)
{
	//Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	int width, height;
	unsigned char* image = SOIL_load_image(texName, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception("Failed to load texture file");


	glGenTextures(1, &texture0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	// freeing unnecessary texture stuff
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void WallsModel::bindTexture(GLuint progID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(progID, "Texture0"), 0);
}
