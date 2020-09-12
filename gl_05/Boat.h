#ifndef boat_h
#define boat_h

#include <iostream>
#include <vector>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "shprogram.h"
#include "Texture.h"

class Boat {
private:
	GLuint VBO, VAO, EBO, texture;
	GLuint VBO2, VAO2, EBO2;
	ShaderProgram shader, shader2;
	vector<GLfloat> vertices, vertices2;
	vector<GLuint> indices, indices2;

	void setBuffers();
	GLuint setTexture();
public:
	Boat();
	void draw(glm::mat4 projection, glm::mat4 view, GLfloat xBoatPos);
};

#endif