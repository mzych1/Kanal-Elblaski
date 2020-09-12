#ifndef raft_h
#define raft_h

#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Cube.h"
#include "shprogram.h"
#include "Texture.h"
#include "Wheel.h"

class Raft {
private:
	GLuint VBO, VAO, EBO, texture;
	ShaderProgram baseShader;
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	Wheel rightFrontWheel, leftFrontWheel, rightBackWheel, leftBackWheel;

	void setBuffers();
	GLuint setTexture();
public:
	Raft();
	void draw(glm::mat4 projection, glm::mat4 view, GLfloat angle, GLfloat xBoatPos);
};

#endif