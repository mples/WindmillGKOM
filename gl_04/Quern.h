#pragma once
#include<vector>
class Quern
{
public:
	GLuint VAO;
	GLuint VBO;
	GLuint texture0;
	std::vector<GLfloat> quernCoord;
	Quern(GLfloat size, glm::vec3 color);
	~Quern();
	void addBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 trans, GLfloat size);
	void draw(const glm::mat4& modelTrans, GLuint modelLoc) const;
	void addQuern(GLuint vertNumb,GLfloat size, GLfloat radius, GLfloat height, glm::vec3 origin, glm::vec3 trans, glm::vec3 color);
	void setTexture(const char* texName);
	void bindTexture(GLuint progID);
};

