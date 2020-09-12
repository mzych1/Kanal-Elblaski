#include "Grass.h"

Grass::Grass() : shader("texture.vert", "texture.frag")
{
	vertices = {
		// coordinates					                //color                //texture
		GRASS_WIDTH / 4, -2.0f, -GRASS_WIDTH / 2,	    1.0f, 1.0f, 1.0f,		4.0f,  0.0f,
		GRASS_WIDTH / 4, -2.0f, GRASS_WIDTH / 2,	    1.0f, 1.0f, 1.0f,		0.0f,  0.0f,
		-GRASS_WIDTH / 2, 0.0f, GRASS_WIDTH / 2,		1.0f, 1.0f, 1.0f,		0.0f,  4.0f,
		-GRASS_WIDTH / 2, 0.0f, -GRASS_WIDTH / 2,		1.0f, 1.0f, 1.0f,		4.0f,  4.0f
	};

	indices = {
		0, 1, 2,
		0, 2, 3,
	};
	setBuffers();
	texture = setTexture();
}

void Grass::setBuffers()
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

GLuint Grass::setTexture()
{
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	return LoadMipmapTexture(GL_TEXTURE0, "textures/grass.jpg");
}

void Grass::draw(glm::mat4 projection, glm::mat4 view)
{
	shader.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.get_programID(), "Texture0"), 0);

	GLint viewLoc = glGetUniformLocation(shader.get_programID(), "view");
	GLint projLoc = glGetUniformLocation(shader.get_programID(), "projection");
	//wys³anie macierzy pod odpowiednie lokalizacje
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}