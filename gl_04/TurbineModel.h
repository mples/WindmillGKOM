#pragma once
#include<vector>

class TurbineModel
{
public:
	GLuint VAO;
	GLuint VBO;
	GLuint texture0;
	std::vector<GLfloat> turbineCoord;
	TurbineModel(GLfloat size, glm::vec3 color, GLfloat texDensity);
	~TurbineModel();

	void draw(const glm::mat4& modelTrans, GLuint modelLoc) const;

	void setTexture(const char* texName);

	void bindTexture(GLuint progID);

	void addBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity);
};

