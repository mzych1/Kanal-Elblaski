#include "Raft.h"

Raft::Raft() : baseShader("boat.vert", "boat.frag"), rightFrontWheel(8, 0.14, glm::vec3(0.0f, 0.0f, 0.0f)), leftFrontWheel(8, 0.14, glm::vec3(0.0f, 0.0f, 0.0f)),
rightBackWheel(8, 0.14, glm::vec3(0.0f, 0.0f, 0.0f)), leftBackWheel(8, 0.14, glm::vec3(0.0f, 0.0f, 0.0f))
{
	vertices = {
		// coordinates				//color					//texture
		0.8f, 0.0f, -0.4f,			0.0f, 1.0f, 1.0f,		0.0f, 1.0f,		//0 
		-0.8f, 0.0f, -0.4f,			0.0f, 1.0f, 1.0f,		0.0f, 0.0f,		//1 
		-0.8f, 0.0f, 0.4f,			0.0f, 1.0f, 1.0f,		1.0f, 0.0f,		//2 
		0.8f, 0.0f, 0.4f,			0.0f, 1.0f, 1.0f,		1.0f, 1.0f,		//3 
		0.8f, -0.05f, -0.4f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,		//4 
		-0.8f, -0.05f, -0.4f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f,		//5 
		-0.8f, -0.05f, 0.4f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f,		//6 
		0.8f, -0.05f, 0.4f,			0.0f, 1.0f, 1.0f,		1.0f, 1.0f		//7 
	};

	indices = {
		0, 1, 3,
		1, 2, 3,
		5, 4, 7,
		7, 6, 5,
		4, 5, 0,
		5, 1, 0,
		5, 6, 1,
		1, 6, 2,
		7, 0, 3,
		7, 4, 0,
		6, 3, 2,
		6, 7, 3,
	};

	setBuffers();
	texture = setTexture();
	rightFrontWheel.create(glm::vec3(1.0f, 0.5f, 0.14f));
	leftFrontWheel.create(glm::vec3(1.0f, 0.5f, 0.14f));
	rightBackWheel.create(glm::vec3(1.0f, 0.5f, 0.14f));
	leftBackWheel.create(glm::vec3(1.0f, 0.5f, 0.14f));
}

void Raft::setBuffers()
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

GLuint Raft::setTexture()
{
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	return LoadMipmapTexture(GL_TEXTURE0, "textures/wood.jpg");
}

void Raft::draw(glm::mat4 projection, glm::mat4 view, GLfloat angle, GLfloat xBoatPos)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = translate(model, glm::vec3(0.2f, 0.3f, 0.0f));
	model = glm::rotate(model, glm::radians(-5.1f), glm::vec3(0.0, 0.0, 1.0));  //obrót - ¿eby ³ódŸ by³a równoleg³a do trawy
	model = translate(model, glm::vec3(-0.2f, -1.5f, -0.08f));

	GLfloat yBoatPos = -0.0889f * xBoatPos;// +1.3333f;
	glm::mat4 transformation = glm::mat4(1.0f);
	transformation = translate(transformation, glm::vec3(xBoatPos, yBoatPos, 0.0f));

	baseShader.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(baseShader.get_programID(), "Texture0"), 0);

	//pobranie lokalizacji zmiennych w progamie shadera
	GLint viewLoc = glGetUniformLocation(baseShader.get_programID(), "view");
	GLint projLoc = glGetUniformLocation(baseShader.get_programID(), "projection");
	GLuint modelLoc = glGetUniformLocation(baseShader.get_programID(), "model");
	GLuint transLoc = glGetUniformLocation(baseShader.get_programID(), "transformation");
	//wys³anie macierzy pod odpowiednie lokalizacje
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transformation));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	rightFrontWheel.drawRaftWheel(projection, view, angle, xBoatPos, glm::vec3(0.3f, -1.22f, 0.32f));
	leftFrontWheel.drawRaftWheel(projection, view, angle, xBoatPos, glm::vec3(0.3f, -1.22f, -0.51f));
	rightBackWheel.drawRaftWheel(projection, view, angle, xBoatPos, glm::vec3(-0.6f, -1.14f, 0.32f));
	leftBackWheel.drawRaftWheel(projection, view, angle, xBoatPos, glm::vec3(-0.6f, -1.14f, -0.51f));
}