#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>

#define STEP 15

static class Camera {
private:
	GLfloat rot_angle;  //k�t obrotu wyra�ony w stopniach
	GLfloat cameraX;  //wsp�rz�dna x po�o�enia kamery
	GLfloat cameraHeight;  //wysoko�� z kt�rej obserwujemy scen� (wsp�rz�dna y po�o�enia kamery)
	GLfloat cameraZ;  //wsp�rz�dna z po�o�enia kamery
	GLfloat watchedPointX;  //wsp�rz�dna x punktu na kt�ry skierowana jest kamera
	GLfloat watchedPointY;  //wsp�rz�dna y punktu na kt�ry skierowana jest kamera
	GLfloat watchedPointZ;  //wsp�rz�dna z punktu na kt�ry skierowana jest kamera

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