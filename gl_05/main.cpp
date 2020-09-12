#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"
#include "RailTrack.h"
#include "Camera.h"
#include "Wheel.h"
#include "Skybox.h"
#include "water.h"
#include "Grass.h"
#include "Boat.h"
#include "Raft.h"

using namespace std;
#define GLM_SWIZZLE

const GLuint WIDTH = 1920, HEIGHT = 1080;
Camera camera;
GLfloat xBoatPos = 0.0;
GLfloat angle = 0.0f;
GLfloat wheelSpeed = 0.5f;	//parametr szybkosci obrotu kola

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - Kanal Elblaski", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, WIDTH, HEIGHT);

		//tworzenie obiektów
		RailTrack track(21);
		track.generateTrack();
		RailTrack track2(21);
		track2.generateTrack();
		Wheel wheel(8, 0.5, glm::vec3(0.f, 0.f, 1.f));
		wheel.create(glm::vec3(0.0f, 0.0f, 1.0f));
		Skybox skybox = Skybox();
		Water water = Water();
		Grass grass = Grass();
		Boat boat = Boat();
		Raft raft = Raft();

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.setMatrixes(WIDTH, HEIGHT); //ustawienie macierzy view i projection

			//rysowanie obiektow
			water.draw(camera.getProjection(), camera.getView());
			skybox.draw(camera.getProjection(), camera.getView());
			boat.draw(camera.getProjection(), camera.getView(), xBoatPos);
			track.drawRailTrack(camera.getProjection(), camera.getView());
			track2.drawRailTrack(camera.getProjection(), camera.getView(), 4.0f);
			grass.draw(camera.getProjection(), camera.getView());
			wheel.draw(camera.getProjection(), camera.getView(), angle);
			raft.draw(camera.getProjection(), camera.getView(), angle, xBoatPos);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;  //wy³¹czenie programu - klawisz 'q'
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_D)  //obrót kamery w prawo - klawisz 'd'
		camera.rotRight();
	if (key == GLFW_KEY_A)  //obrót kamery w lewo - klawisz 'a'
		camera.rotLeft();
	if (key == GLFW_KEY_S)  //kamera do do³u - klawisz 's'
		camera.rotDown();
	if (key == GLFW_KEY_W)  //kamera do góry - klawisz 'w'
		camera.rotUp();
	if (key == GLFW_KEY_UP)  //kamera do przodu - strza³ka w przód
		camera.moveForward();
	if (key == GLFW_KEY_DOWN)  //kamera do ty³u - strza³ka w ty³
		camera.moveBackward();
	if (key == GLFW_KEY_LEFT)  //kamera w lewo - strza³ka w lewo
		camera.moveLeft();
	if (key == GLFW_KEY_RIGHT)  //kamera w prawo - strza³ka w prawo
		camera.moveRight();
	if (key == GLFW_KEY_U)
		camera.moveUp();
	if (key == GLFW_KEY_J)
		camera.moveDown();
	if (key == GLFW_KEY_M)
	{
		xBoatPos += 0.1;
		if (xBoatPos >= 6.8f)
			xBoatPos = 6.8f;
		else
		{
			angle += wheelSpeed;
			if (angle >= 360.f) angle = 0;
		}
	}
	if (key == GLFW_KEY_N)
	{
		xBoatPos -= 0.1;
		if (xBoatPos <= 0.0f)
			xBoatPos = 0.0f;
		else
		{
			angle -= wheelSpeed;
			if (angle <= -360.f) angle = 0;
		}
	}
}