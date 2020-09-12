#include "RailTrack.h"

void RailTrack::generateTrack()
{
	glm::vec3 startPositionTie(-0.8f, -1.03f, -0.45f);
	glm::vec3 dimensionsTie(0.16f, 0.03f, 0.72f);
	glm::vec3 colorTie(0.1f, 0.f, 0.f);

	glm::vec3 startPosition(-0.9f, -1.0f, -0.44f);
	glm::vec3 dimensions(0.4f, 0.02f, 0.04f);
	glm::vec3 color(0.1f, 0.1f, 0.1f);

	float gapX = 0.4;	//roztaw belek 

	float gapZ = 0.7;	//rozstaw szyn

	for (int i = 0; i < railroadTiesNumber; ++i)
	{
		Cube cube(startPositionTie, dimensionsTie, colorTie);
		cube.create();
		cubesCollection.push_back(cube);

		startPositionTie.x += gapX;


		Cube leftRail(startPosition, dimensions, color);
		leftRail.create();
		cubesCollection.push_back(leftRail);

		startPosition.z += gapZ;

		Cube rightRail(startPosition, dimensions, color);
		rightRail.create();
		cubesCollection.push_back(rightRail);

		startPosition.z -= gapZ;
		startPosition.x += dimensions.x;


		//DEBUG
		std::cout << "szyna: " << startPosition.x << " " ;
		std::cout << "belka: " << startPositionTie.x << " ";
	}
}

void RailTrack::drawRailTrack(glm::mat4 projection, glm::mat4 view, GLfloat translation)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = translate(model, glm::vec3(-0.8f, -1.0f, -0.2f));
	model = glm::rotate(model, glm::radians(-5.1f), glm::vec3(0.0, 0.0, 1.0));  //obrót - ¿eby tor by³ równoleg³y do trawy
	model = translate(model, glm::vec3(0.8f, 1.0f, 0.2f));
	model = translate(model, glm::vec3(0.0f, -0.24f, translation));

	shader.Use();

	GLint viewLoc = glGetUniformLocation(shader.get_programID(), "view");
	GLint projLoc = glGetUniformLocation(shader.get_programID(), "projection");
	GLint modelLoc = glGetUniformLocation(shader.get_programID(), "model");
	//wys³anie macierzy pod odpowiednie lokalizacje
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	for (auto el : cubesCollection)
	{
		el.drawCube();
	}
}
