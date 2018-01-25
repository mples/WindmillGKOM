#pragma once
#include<vector>

class WallsModel
{
public:

	GLuint VAO;
	GLuint VBO;
	GLuint texture0;
	std::vector<GLfloat> wallsCoord;
	WallsModel(GLfloat size, glm::vec3 color);
	~WallsModel();
	void draw(const glm::mat4& modelTrans, GLuint modelLoc) const;
	void setTexture(const char* texName);
	void bindTexture(GLuint progID);
};

