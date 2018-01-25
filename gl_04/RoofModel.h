#pragma once
#include<vector>

class RoofModel
{
public:
	GLuint VAO;
	GLuint VBO;
	GLuint texture0;
	RoofModel(GLfloat size, glm::vec3 color);
	~RoofModel();
	std::vector<GLfloat> roofCoord;
	void draw(const glm::mat4& modelTrans, GLuint modelLoc) const;
	void bindTexture(GLuint progID);
	void setTexture(const char* texName);
	
};

