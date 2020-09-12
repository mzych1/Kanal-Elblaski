#include <vector>
#include <string>
#include <SOIL.h>
#include <GL/glew.h>
#include <iostream>
#include "shprogram.h"

class Skybox
{
private:
	GLuint VBO, VAO, textureId;
	ShaderProgram skyboxShader;
	std::vector<GLfloat> vertices;
	std::vector<std::string> faces;

	void setBuffers();
	GLuint loadCubemap(std::vector<std::string> faces);

public:
	Skybox();
	void draw(glm::mat4 projection, glm::mat4 view);
};