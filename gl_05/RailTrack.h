#pragma once
#include <vector>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include "Cube.h"
#include "shprogram.h"

class RailTrack
{
	unsigned railroadTiesNumber;
	std::vector<Cube> cubesCollection;
	ShaderProgram shader;
public:
	RailTrack(unsigned nr) : railroadTiesNumber(nr), shader("transform.vert", "transform.frag") {}
	void generateTrack();
	void drawRailTrack(glm::mat4 projection, glm::mat4 view, GLfloat translation = 0.0f);
};

