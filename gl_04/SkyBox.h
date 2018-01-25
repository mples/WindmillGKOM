#pragma once
class SkyBox
{
public:
	GLuint VAO;
	GLuint VBO;
	GLuint texture0;
	std::vector<GLfloat> skyBoxCoord;
	SkyBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity);
	~SkyBox();
	void draw(const glm::mat4& modelTrans, GLuint modelLoc) const;
	void setTexture(const char* texName);
	void bindTexture(GLuint progID);
	void addBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity);
};

