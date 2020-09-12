#pragma once
#include "Cube.h"
#include "shprogram.h"

class Wheel
{
	int barsNumber;
	GLfloat radius;
	glm::vec3 centerCoord;

	GLfloat phi;
	GLfloat barLength;

	ShaderProgram shader;
	std::vector<Cube> elementsCollection;

public:
	Wheel(int number, GLfloat radius, glm::vec3 centerCoord) : barsNumber(number), radius(radius), centerCoord(centerCoord), shader("shWheel.vert", "shWheel.frag") {}


	void create(glm::vec3 color);
	void draw(glm::mat4 projection, glm::mat4 view, GLfloat angle);
	void drawRaftWheel(glm::mat4 projection, glm::mat4 view, GLfloat angle, GLfloat xBoatPos, glm::vec3 translation);
};

