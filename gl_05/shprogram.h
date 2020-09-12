#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

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
	
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
	}
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
};