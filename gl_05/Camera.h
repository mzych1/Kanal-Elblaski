#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>

#define STEP 15

static class Camera {
private:
	GLfloat rot_angle;  //k¹t obrotu wyra¿ony w stopniach
	GLfloat cameraX;  //wspó³rzêdna x po³o¿enia kamery
	GLfloat cameraHeight;  //wysokoœæ z której obserwujemy scenê (wspó³rzêdna y po³o¿enia kamery)
	GLfloat cameraZ;  //wspó³rzêdna z po³o¿enia kamery
	GLfloat watchedPointX;  //wspó³rzêdna x punktu na który skierowana jest kamera
	GLfloat watchedPointY;  //wspó³rzêdna y punktu na który skierowana jest kamera
	GLfloat watchedPointZ;  //wspó³rzêdna z punktu na który skierowana jest kamera

	glm::mat4 view;  //macierz widoku
	glm::mat4 projection;  //macierz rzutowania

public:
	Camera();
	void setMatrixes(const GLuint WIDTH, const GLuint HEIGHT);
	glm::mat4 getView();
	glm::mat4 getProjection();

	void rotRight();
	void rotLeft();
	void rotDown();
	void rotUp();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};