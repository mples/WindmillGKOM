#pragma once
#include "shprogram.h"

class Lamp
{
public:
	GLuint VAO;
	GLuint VBO;
	GLuint texture0;
	ShaderProgram *shader;
	glm::mat4 modelLamp;
	glm::mat4 viewLamp;
	glm::mat4 projectionLamp;
	std::vector<GLfloat> lampCoord;
	Lamp(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity);
	~Lamp();
	void draw(const glm::mat4& modelTrans, GLuint modelLoc) const;
	void setTexture(const char* texName);
	void bindTexture(GLuint progID);
	void addBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity);
};

