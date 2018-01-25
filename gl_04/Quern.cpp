#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <iostream>
#include "Quern.h"

static GLfloat boxMesh[] = {

	//front
	-0.5f, -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	0.5f,  0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	0.5f,  0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	-0.5f,  0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,

	//back
	-0.5f, -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	-0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,

	//right
	0.5f, 0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	0.5f,  0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,
	0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,

	//left
	-0.5f, 0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	-0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	-0.5f,  0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,
	-0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,

	//up
	0.5f, 0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	-0.5f,  0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,

	//down
	0.5f, -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 0.0f, 1.0f,
	-0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	0.5f,  -0.5f, 0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 1.0f,
	-0.5f,  -0.5f, -0.5f,		0.56f, 0.27f, 0.19f,		 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,			0.56f, 0.27f, 0.19f,		 1.0f, 0.0f,

};


Quern::Quern(GLfloat size, glm::vec3 color)
{
	

	addQuern(24, size, 0.5f, 0.3f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), color);
	//addQuern(24, size, 0.5f, 0.3f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -0.15f, 0.0f), color);

	//addBox(0.1f, 2.1f, 0.1f , glm::vec3(0.0f, 0.5f, 0.0f), size);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * quernCoord.size(), &(quernCoord[0]), GL_STATIC_DRAW);

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


Quern::~Quern()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Quern::addBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size)
{
	for (int i = 0; i < _countof(boxMesh) / 8; ++i) {
		glm::vec4 poss(boxMesh[i * 8] * size * width,
			boxMesh[i * 8 + 1] * size * height,
			boxMesh[i * 8 + 2] * size * depth,
			1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, move);
		poss = trans * poss;


		quernCoord.push_back(poss.x);
		quernCoord.push_back(poss.y);
		quernCoord.push_back(poss.z);
		quernCoord.push_back(boxMesh[i * 8 + 3]);
		quernCoord.push_back(boxMesh[i * 8 + 4]);
		quernCoord.push_back(boxMesh[i * 8 + 5]);
		quernCoord.push_back(boxMesh[i * 8 + 6]);
		quernCoord.push_back(boxMesh[i * 8 + 7]);
	}
}

void Quern::draw(const glm::mat4 & modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)quernCoord.size());

	glBindVertexArray(0);
}

void Quern::addQuern(GLuint vertNumb,GLfloat size, GLfloat radius, GLfloat height, glm::vec3 origin, glm::vec3 move, glm::vec3 color)
{

	height *= size;

	glm::vec4 point(-radius * size, 0.0f, 0.0f, 1.0f);
	glm::vec4 originPoint(origin.x,origin.y,origin.z, 1.0f);
	glm::mat4 moveMat;
	moveMat = glm::translate(moveMat, move);

	originPoint = moveMat * originPoint;

	point = moveMat * point;

	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(360.0f / vertNumb), glm::vec3(0.0f, 1.0f, 0.0f));
	point = trans * point;

	glm::vec3 normalUp(0.0f, 1.0f, 0.0f);
	glm::vec3 normalDown(0.0f, -1.0f, 0.0f);
	glm::vec4 normalSide(0.0f, 0.0f, 1.0f, 1.0f);


	normalSide = trans * normalSide;
	normalSide = glm::normalize(normalSide);

	for (int i = 0; i < vertNumb; ++i) {
		//first poin
		quernCoord.push_back(point.x);
		quernCoord.push_back(point.y);
		quernCoord.push_back(point.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalUp.x);
		quernCoord.push_back(normalUp.y);
		quernCoord.push_back(normalUp.z);

		quernCoord.push_back(0.0f);
		quernCoord.push_back(0.0f);

		quernCoord.push_back(originPoint.x);
		quernCoord.push_back(originPoint.y);
		quernCoord.push_back(originPoint.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalUp.x);
		quernCoord.push_back(normalUp.y);
		quernCoord.push_back(normalUp.z);

		quernCoord.push_back(0.5f);
		quernCoord.push_back(0.5f);

		glm::vec4 prevPoint(point.x, point.y, point.z, 1.0f);
		glm::vec4 prevNormalSide(normalSide.z, normalSide.y, normalSide.z, 1.0f);
		point = trans * point;
		normalSide = trans * normalSide;
		normalSide = glm::normalize(normalSide);

		quernCoord.push_back(point.x);
		quernCoord.push_back(point.y);
		quernCoord.push_back(point.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalUp.x);
		quernCoord.push_back(normalUp.y);
		quernCoord.push_back(normalUp.z);

		quernCoord.push_back(1.0f);
		quernCoord.push_back(0.0f);

		//sides

		quernCoord.push_back(prevPoint.x);
		quernCoord.push_back(prevPoint.y);
		quernCoord.push_back(prevPoint.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(prevNormalSide.x);
		quernCoord.push_back(prevNormalSide.y);
		quernCoord.push_back(prevNormalSide.z);

		quernCoord.push_back(1.0f);
		quernCoord.push_back(1.0f);
		//
		quernCoord.push_back(point.x);
		quernCoord.push_back(point.y);
		quernCoord.push_back(point.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalSide.x);
		quernCoord.push_back(normalSide.y);
		quernCoord.push_back(normalSide.z);

		quernCoord.push_back(0.0f);
		quernCoord.push_back(1.0f);

		//

		quernCoord.push_back(point.x);
		quernCoord.push_back(point.y - height);
		quernCoord.push_back(point.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalSide.x);
		quernCoord.push_back(normalSide.y);
		quernCoord.push_back(normalSide.z);

		quernCoord.push_back(0.0f);
		quernCoord.push_back(0.0f);
		//

		quernCoord.push_back(prevPoint.x);
		quernCoord.push_back(prevPoint.y);
		quernCoord.push_back(prevPoint.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(prevNormalSide.x);
		quernCoord.push_back(prevNormalSide.y);
		quernCoord.push_back(prevNormalSide.z);

		quernCoord.push_back(1.0f);
		quernCoord.push_back(1.0f);
		//

		quernCoord.push_back(point.x);
		quernCoord.push_back(point.y - height);
		quernCoord.push_back(point.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalSide.x);
		quernCoord.push_back(normalSide.y);
		quernCoord.push_back(normalSide.z);

		quernCoord.push_back(0.0f);
		quernCoord.push_back(0.0f);

		//
		quernCoord.push_back(prevPoint.x);
		quernCoord.push_back(prevPoint.y - height);
		quernCoord.push_back(prevPoint.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(prevNormalSide.x);
		quernCoord.push_back(prevNormalSide.y);
		quernCoord.push_back(prevNormalSide.z);

		quernCoord.push_back(1.0f);
		quernCoord.push_back(0.0f);

		//bottom
		quernCoord.push_back(prevPoint.x);
		quernCoord.push_back(prevPoint.y - height);
		quernCoord.push_back(prevPoint.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalDown.x);
		quernCoord.push_back(normalDown.y);
		quernCoord.push_back(normalDown.z);

		quernCoord.push_back(0.0f);
		quernCoord.push_back(0.0f);


		quernCoord.push_back(point.x);
		quernCoord.push_back(point.y - height);
		quernCoord.push_back(point.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalDown.x);
		quernCoord.push_back(normalDown.y);
		quernCoord.push_back(normalDown.z);

		quernCoord.push_back(1.0f);
		quernCoord.push_back(0.0f);

		quernCoord.push_back(originPoint.x);
		quernCoord.push_back(originPoint.y - height);
		quernCoord.push_back(originPoint.z);

		quernCoord.push_back(color.x);
		quernCoord.push_back(color.y);
		quernCoord.push_back(color.z);

		quernCoord.push_back(normalDown.x);
		quernCoord.push_back(normalDown.y);
		quernCoord.push_back(normalDown.z);

		quernCoord.push_back(0.5f);
		quernCoord.push_back(0.5f);

	}
}

void Quern::setTexture(const char * texName)
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

void Quern::bindTexture(GLuint progID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(progID, "Texture0"), 0);
}
