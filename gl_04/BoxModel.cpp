#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <iostream>
#include "BoxModel.h"

static GLfloat boxMesh[] = {

	//front
	-0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
	0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 1.0f, 1.0f,
	0.5f,  0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 1.0f, 0.0f,
	0.5f,  0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 1.0f, 0.0f,
	-0.5f,  0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,		 0.0f, 1.0f,

	//back
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,		 1.0f, 0.0f,
	0.5f,  -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		 1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,			0.0f, 0.0f, -1.0f,		 1.0f, 0.0f,
	-0.5f,  -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,		 0.0f, 0.0f,

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

	//up
	0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,			0.0f, 1.0f, 0.0f,		 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		 0.0f, 0.0f,
	-0.5f,  0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f,			0.0f, 1.0f, 0.0f,		 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		 0.0f, 1.0f,

	//down
	0.5f, -0.5f, 0.5f,			0.0f, -1.0f, 0.0f,		 1.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,			0.0f, -1.0f, 0.0f,		 0.0f, 1.0f,
	-0.5f,  -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,		 0.0f, 0.0f,
	0.5f,  -0.5f, 0.5f,			0.0f, -1.0f, 0.0f,		 1.0f, 1.0f,
	-0.5f,  -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,		 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,			0.0f, -1.0f, 0.0f,		 1.0f, 0.0f,

};

BoxModel::BoxModel(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity)
{
	addBox(width, height, depth, move, size,color,texDensity);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * boxCoord.size(), &(boxCoord[0]), GL_STATIC_DRAW);

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


BoxModel::~BoxModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void BoxModel::draw(const glm::mat4 & modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)boxCoord.size());

	glBindVertexArray(0);
}

void BoxModel::setTexture(const char * texName)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(texName, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception("Failed to load texture file");


	glGenTextures(1, &texture0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void BoxModel::bindTexture(GLuint progID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(progID, "Texture0"), 0);
}

void BoxModel::addBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity)
{
	for (int i = 0; i < _countof(boxMesh) / 8; ++i) {
		glm::vec4 poss(boxMesh[i * 8] * size * width,
			boxMesh[i * 8 + 1] * size * height,
			boxMesh[i * 8 + 2] * size * depth,
			1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, move);
		poss = trans * poss;


		boxCoord.push_back(poss.x);
		boxCoord.push_back(poss.y);
		boxCoord.push_back(poss.z);
		boxCoord.push_back(color.x);
		boxCoord.push_back(color.y);
		boxCoord.push_back(color.z);
		boxCoord.push_back(boxMesh[i * 8 + 3]);
		boxCoord.push_back(boxMesh[i * 8 + 4]);
		boxCoord.push_back(boxMesh[i * 8 + 5]);
		boxCoord.push_back(boxMesh[i * 8 + 6] * texDensity);
		boxCoord.push_back(boxMesh[i * 8 + 7] * texDensity);
	}
}
