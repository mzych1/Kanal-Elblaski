#include "Wheel.h"
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

void Wheel::create(glm::vec3 color)
{
	phi = 360.0f / (float)barsNumber;
	barLength = 2 * sin(glm::radians(0.5 * phi)) * radius;

	// wspolrzedne nowej belki do wyliczenia
	GLfloat x;
	GLfloat y;

	GLfloat angle = 90 + phi / 2;
	GLfloat rotAngle;

	for (int i = 0; i < barsNumber; ++i)
	{
		//radius - wspolrzedna x pierwszego punktu

		rotAngle = glm::radians(i * phi);

		x = centerCoord.x + (radius - centerCoord.x) * cos(rotAngle) - (0.f - centerCoord.y) * sin(rotAngle);
		y = centerCoord.x + (radius - centerCoord.x) * sin(rotAngle) + (0.f - centerCoord.y) * cos(rotAngle);

		Cube bar(glm::vec3(x, y, centerCoord.z), glm::vec3(barLength, 0.03f, 0.03f), color, glm::vec3(0.f, 0.f, 90 + phi / 2 + (i * phi)));
		bar.create();
		elementsCollection.push_back(bar);

		Cube wheelCenter(glm::vec3(centerCoord.x, centerCoord.y - 0.01, centerCoord.z), glm::vec3(radius - 0.03, 0.02f, 0.02f), color, glm::vec3(0.0f, 0.0f, i * phi));
		wheelCenter.create();
		elementsCollection.push_back(wheelCenter);
	}

}

void Wheel::draw(glm::mat4 projection, glm::mat4 view, GLfloat angle)
{
	shader.Use();

	//obrot wokol srodka kola
	glm::mat4 rot = glm::mat4(1.0f);
	rot = translate(rot, centerCoord);
	rot = glm::rotate(rot, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	rot = translate(rot, glm::vec3((-1) * centerCoord.x, (-1) * centerCoord.y, (-1) * centerCoord.z));

	GLint rotLoc = glGetUniformLocation(shader.get_programID(), "rot");
	glUniformMatrix4fv(rotLoc, 1, GL_FALSE, glm::value_ptr(rot));


	// obrot wokol osi Y 
	glm::mat4 rot2 = glm::mat4(1.0f);
	rot2 = glm::rotate(rot2, glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));

	GLint rot2Loc = glGetUniformLocation(shader.get_programID(), "rot2");
	glUniformMatrix4fv(rot2Loc, 1, GL_FALSE, glm::value_ptr(rot2));



	// przesuniecie
	glm::mat4 transl = glm::mat4(1.0f);
	transl = translate(transl, glm::vec3(12.f, -1.5f, 2.0f));

	GLint translLoc = glGetUniformLocation(shader.get_programID(), "transform");
	glUniformMatrix4fv(translLoc, 1, GL_FALSE, glm::value_ptr(transl));

	GLint projlLoc = glGetUniformLocation(shader.get_programID(), "projection");
	glUniformMatrix4fv(projlLoc, 1, GL_FALSE, glm::value_ptr(projection));
	GLint viewlLoc = glGetUniformLocation(shader.get_programID(), "view");
	glUniformMatrix4fv(viewlLoc, 1, GL_FALSE, glm::value_ptr(view));

	for (auto el : elementsCollection)
	{
		el.drawCube(shader.get_programID(), el.coordinates);
	}

}

void Wheel::drawRaftWheel(glm::mat4 projection, glm::mat4 view, GLfloat angle, GLfloat xBoatPos, glm::vec3 translation)
{
	shader.Use();

	//obrot wokol srodka kola
	glm::mat4 rot = glm::mat4(1.0f);
	rot = translate(rot, centerCoord);
	rot = glm::rotate(rot, glm::radians(-20*angle), glm::vec3(0.0f, 0.0f, 1.0f));
	rot = translate(rot, glm::vec3((-1) * centerCoord.x, (-1) * centerCoord.y, (-1) * centerCoord.z));

	GLint rotLoc = glGetUniformLocation(shader.get_programID(), "rot");
	glUniformMatrix4fv(rotLoc, 1, GL_FALSE, glm::value_ptr(rot));


	// obrot wokol osi Y 
	glm::mat4 rot2 = glm::mat4(1.0f);
	GLfloat yBoatPos = -0.0889f * xBoatPos;
	rot2 = translate(rot2, glm::vec3(xBoatPos, yBoatPos, 0.0f));

	GLint rot2Loc = glGetUniformLocation(shader.get_programID(), "rot2");
	glUniformMatrix4fv(rot2Loc, 1, GL_FALSE, glm::value_ptr(rot2));



	// przesuniecie
	glm::mat4 transl = glm::mat4(1.0f);
	transl = translate(transl, translation);

	GLint translLoc = glGetUniformLocation(shader.get_programID(), "transform");
	glUniformMatrix4fv(translLoc, 1, GL_FALSE, glm::value_ptr(transl));

	GLint projlLoc = glGetUniformLocation(shader.get_programID(), "projection");
	glUniformMatrix4fv(projlLoc, 1, GL_FALSE, glm::value_ptr(projection));
	GLint viewlLoc = glGetUniformLocation(shader.get_programID(), "view");
	glUniformMatrix4fv(viewlLoc, 1, GL_FALSE, glm::value_ptr(view));

	for (auto el : elementsCollection)
	{
		el.drawCube(shader.get_programID(), el.coordinates);
	}

}