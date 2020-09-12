#ifndef grass_h
#define grass_h

#include <iostream>
#include <vector>
#include <glm\gtc\type_ptr.hpp>
#include "shprogram.h"
#include "Texture.h"

#define GRASS_WIDTH 30.0f

class Grass {
private:
	GLuint VBO, VAO, EBO, texture;
	ShaderProgram shader;
	vector<GLfloat> vertices;
	vector<GLuint> indices;

	void setBuffers();
	GLuint setTexture();
public:
	Grass();
	void draw(glm::mat4 projection, glm::mat4 view);
};

#endif