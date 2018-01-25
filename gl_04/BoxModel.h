#pragma once
class BoxModel
{
public:
	GLuint VAO;
	GLuint VBO;
	GLuint texture0;
	std::vector<GLfloat> boxCoord;
	BoxModel(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity);
	~BoxModel();
	void draw(const glm::mat4& modelTrans, GLuint modelLoc) const;
	void setTexture(const char* texName);
	void bindTexture(GLuint progID);
	void addBox(GLfloat width, GLfloat height, GLfloat depth, glm::vec3 move, GLfloat size, glm::vec3 color, GLfloat texDensity);
};

