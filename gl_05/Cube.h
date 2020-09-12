#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Cube
{
public:
	glm::vec3 coordinates;
	glm::vec3 size;
	glm::vec3 col;
	glm::vec3 rotation;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	std::vector<GLfloat> vertices2;

	GLuint VBO, EBO, VAO;

public:

	Cube(glm::vec3 coordinates, glm::vec3 dimensions, glm::vec3 color, glm::vec3 rotation) :
		coordinates(coordinates), size(dimensions), col(color), rotation(rotation) {}

	Cube(glm::vec3 coordinates, glm::vec3 dimensions, glm::vec3 color) :
		coordinates(coordinates), size(dimensions), col(color), rotation(glm::vec3(0.f, 0.f, 0.f)) {}

	void drawCube(GLuint progID, glm::vec3 rotPoint);

	void generateVertices();
	void generateIndices();

	void joinCoordCol();

	void createBuffers();
	void drawCube();

	void drawCube(GLuint progID);

	void displayVertices();
	void displayIndices();

	void create();
};

