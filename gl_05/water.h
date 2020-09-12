#ifndef water_h
#define water_h

#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "shprogram.h"
#include "Grass.h"

class Water {
private:
	GLuint VBO, VAO, EBO;
	ShaderProgram waterShader;
	vector<GLfloat> vertices;
	vector<GLuint> indices;

	void setBuffers();
public:
	Water();
	void draw(glm::mat4 projection, glm::mat4 view);
};

#endif