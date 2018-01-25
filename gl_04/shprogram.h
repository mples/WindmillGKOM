#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class ShaderProgram
{
	GLuint program_id; 	// The program ID
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

	// Use the program
	void Use() const
	{
		glUseProgram(get_programID());
	}

	// returns program ID
	GLuint get_programID() const
	{
		return program_id;
	}
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(get_programID(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(get_programID(), name.c_str()), 1, &value[0]);
	}
};