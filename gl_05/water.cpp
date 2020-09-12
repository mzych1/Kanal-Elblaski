#include "water.h"
#include <glm\gtc\type_ptr.hpp>

Water::Water() : waterShader("water.vert", "water.frag")
{

	vertices = {
		// coordinates					
		GRASS_WIDTH / 4, -2.0f, -GRASS_WIDTH / 2,
		GRASS_WIDTH / 4, -2.0f, GRASS_WIDTH / 2,
		GRASS_WIDTH, -2.0f, GRASS_WIDTH / 2,
		GRASS_WIDTH, -2.0f, -GRASS_WIDTH / 2,
	};
	indices = {
		0, 1, 2,
		0, 2, 3,
	};
	setBuffers();
}

void Water::setBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void Water::draw(glm::mat4 projection, glm::mat4 view)
{
	waterShader.Use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLint projectionLoc = glGetUniformLocation(waterShader.get_programID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint viewLoc = glGetUniformLocation(waterShader.get_programID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}