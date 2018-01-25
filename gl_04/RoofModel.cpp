#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <iostream>
#include "WallsModel.h"
#include "RoofModel.h"

static GLfloat roofMesh[] = {

	0.5f, 0.5f, 0.5f,			0.7f, 0.7f, 0.7f,		 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f,			0.7f, 0.7f, -0.7f,		 1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,			0.0f, 1.0f, 0.0f,		 0.5f, 0.5f,

	0.5f,  0.5f, 0.5f,			0.7f, 0.7f, 0.7f,		 1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,			0.0f, 1.0f, 0.0f,		 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,			-0.7f, 0.7f, 0.7f,		 0.0f, 0.0f,

	-0.5f,  0.5f, 0.5f,			-0.7f, 0.7f, 0.7f,		 0.0f, 0.0f,
	0.0f,  1.0f, 0.0f,			0.0f, 1.0f, 0.0f,		 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,			-0.7f, 0.7f, -0.7f,		 1.0f, 0.0f,

	0.5f,  0.5f, -0.5f,			0.7f, 0.7f, -0.7f,		 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,			-0.7f, 0.7f, -0.7f,		 1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,			0.0f, 1.0f, 0.0f,		 0.5f, 0.5f,


};

RoofModel::RoofModel(GLfloat size, glm::vec3 color)
{
	for (int i = 0; i < _countof(roofMesh) / 8; ++i)
	{
		roofCoord.push_back(roofMesh[i * 8] * size);
		roofCoord.push_back(roofMesh[i * 8 + 1] * size);
		roofCoord.push_back(roofMesh[i * 8 + 2] * size);
		roofCoord.push_back(color.x);
		roofCoord.push_back(color.y);
		roofCoord.push_back(color.z);
		roofCoord.push_back(roofMesh[i * 8 + 3]);
		roofCoord.push_back(roofMesh[i * 8 + 4]);
		roofCoord.push_back(roofMesh[i * 8 + 5]);
		roofCoord.push_back(roofMesh[i * 8 + 6]);
		roofCoord.push_back(roofMesh[i * 8 + 7]);
	}

	for (int i = 0; i < _countof(roofMesh) / 8; ++i)
	{
		roofCoord.push_back((roofMesh[i * 8] * size) /*- 0.1f*/);
		roofCoord.push_back((roofMesh[i * 8 + 1] * size) - 0.1f);
		roofCoord.push_back((roofMesh[i * 8 + 2] * size) /* -0.1f*/);
		roofCoord.push_back(color.x);
		roofCoord.push_back(color.y);
		roofCoord.push_back(color.z);
		roofCoord.push_back(roofMesh[i * 8 + 3] * -1.0f);
		roofCoord.push_back(roofMesh[i * 8 + 4] * -1.0f);
		roofCoord.push_back(roofMesh[i * 8 + 5] * -1.0f);
		roofCoord.push_back(roofMesh[i * 8 + 6]);
		roofCoord.push_back(roofMesh[i * 8 + 7]);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * roofCoord.size(), &(roofCoord[0]), GL_STATIC_DRAW);

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


RoofModel::~RoofModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void RoofModel::draw(const glm::mat4 & modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)roofCoord.size());

	glBindVertexArray(0);
}

void RoofModel::bindTexture(GLuint progID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(progID, "Texture0"), 0);
}

void RoofModel::setTexture(const char * texName)
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


