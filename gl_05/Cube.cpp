#include "Cube.h"
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

void Cube::drawCube()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Cube::drawCube(GLuint progID, glm::vec3 rotPoint)
{

	glm::mat4 model = glm::mat4(1.0f);
	if (!(rotation.x == 0.f && rotation.y == 0.f && rotation.z == 0.f)) {
		model = translate(model, rotPoint);
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = translate(model, glm::vec3((-1) * rotPoint.x, (-1) * rotPoint.y, (-1) * rotPoint.z));
	}


	GLint modelLoc = glGetUniformLocation(progID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cube::generateVertices()
{
	// tylna sciana
	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z);

	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z);


	//przednia sciana
	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z + size.z);


	//lewa sciana
	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z);

	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z);


	//prawa sciana
	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z);


	//dolna sciana
	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z);

	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y);
	vertices.push_back(coordinates.z);


	//gorna sciana
	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z);

	vertices.push_back(coordinates.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z + size.z);

	vertices.push_back(coordinates.x + size.x);
	vertices.push_back(coordinates.y + size.y);
	vertices.push_back(coordinates.z);

}

void Cube::generateIndices()
{
	int x = 0;
	for (int i = 0; i < 6; ++i) {

		indices.push_back(x);
		indices.push_back(x + 1);
		indices.push_back(x + 2);
		indices.push_back(x);
		indices.push_back(x + 2);
		indices.push_back(x + 3);

		x += 4;
	}
}

void Cube::joinCoordCol()
{
	for (int i = 0; i < 72; )
	{
		for (int j = 0; j < 3; ++j)
		{
			vertices2.push_back(vertices[i]);
			++i;
		}

		//na razie roboczo kazdy wierzcholek czerwony
		vertices2.push_back(col.x);
		vertices2.push_back(col.y);
		vertices2.push_back(col.z);
	}
}

void Cube::createBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(vertices2[0]), &vertices2[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);


	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

}

void Cube::displayVertices() {
	for (int i = 0; i < 72; )
	{
		for (int j = 0; j < 6; ++j)
		{
			std::cout << vertices2[i] << " ";
			++i;
		}
		std::cout << std::endl;
	}
}

void Cube::displayIndices() {
	for (int i = 0; i < 36; )
	{
		for (int j = 0; j < 6; ++j)
		{
			std::cout << indices[i] << " ";
			++i;
		}
		std::cout << std::endl;
	}
}

void Cube::create()
{
	generateVertices();
	generateIndices();
	joinCoordCol();

	createBuffers();
}



