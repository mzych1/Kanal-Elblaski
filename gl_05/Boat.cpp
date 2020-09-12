#include "Boat.h"

Boat::Boat() : shader("boat.vert", "boat.frag"), shader2("simple.vert", "simple.frag")
{
	vertices = {
		// coordinates				//color					//texture
		-0.6f, 0.6f, 0.4f,			1.0f, 1.0f, 1.0f,		0.6f, 0.0f,		//0 -
		-0.6f, 0.6f, 0.4f,			1.0f, 0.5f, 1.0f,		1.0f, 1.0f,		//1 
		-0.6f, 0.6f, -0.4f,			0.0f, 1.0f, 1.0f,		0.6f, 0.0f,		//2 -
		0.6f, 0.6f, -0.4f,			1.0f, 0.6f, 0.3f,		0.6f, 1.0f,		//3 -
		1.0f, 0.6f, 0.0f,			0.0f, 0.0f, 0.4f,		0.0f, 0.0f,		//4 
		0.6f, 0.6f, 0.4f,			1.0f, 1.0f, 0.5f,		0.6f, 1.0f,		//5 -
		-0.6f, 0.0f, 0.1f,			1.0f, 0.0f, 0.0f,		0.9f, 0.1f,		//6 
		-0.6f, 0.0f, -0.1f,			1.0f, 1.1f, 0.7f,		1.0f, 0.0f,		//7 -
		0.6f, 0.0f, 0.0f,			0.0f, 0.0f, 0.8f,		1.0f, 1.0f		//8 -
	};

	indices = {
		//góra
		0, 2, 5,
		2, 3, 5,
		5, 3, 4,
		//ty³
		6, 1, 0,
		6, 7, 1,
		7, 2, 1,
		//dó³
		6, 7, 8,
		//przód
		8, 4, 3,
		8, 5, 4,
		//boki
		7, 8, 3,
		7, 3, 2,
		6, 0, 5,
		8, 6, 5
	};

	vertices2 = {
		// coordinates				//color			
		-0.6f, 0.601f, 0.4f,			1.0f, 1.0f, 1.0f,
		-0.6f, 0.601f, 0.4f,			1.0f, 1.0f, 1.0f,
		-0.6f, 0.601f, -0.4f,		1.0f, 1.0f, 1.0f,
		0.6f, 0.601f, -0.4f,			1.0f, 1.0f, 1.0f,
		1.0f, 0.601f, 0.0f,			1.0f, 1.0f, 1.0f,
		0.6f, 0.601f, 0.4f,			1.0f, 1.0f, 1.0f
	};
	indices2 = {
		//góra
		0, 2, 5,
		2, 3, 5,
		5, 3, 4
	};

	setBuffers();
	texture = setTexture();
}

void Boat::setBuffers()
{
	//oteksturowana czêœæ ³ódki
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

	//bia³a góra
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(vertices2[0]), &vertices2[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(indices2[0]), &indices2[0], GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

GLuint Boat::setTexture()
{
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	return LoadMipmapTexture(GL_TEXTURE0, "textures/metal.jpg");
}

void Boat::draw(glm::mat4 projection, glm::mat4 view, GLfloat xBoatPos)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = translate(model, glm::vec3(0.2f, 0.3f, 0.0f));
	model = glm::rotate(model, glm::radians(-5.1f), glm::vec3(0.0, 0.0, 1.0));  //obrót - ¿eby ³ódŸ by³a równoleg³a do trawy
	model = translate(model, glm::vec3(-0.2f, -1.5f, -0.08f));

	GLfloat yBoatPos = -0.0889f * xBoatPos;
	glm::mat4 transformation = glm::mat4(1.0f);
	transformation = translate(transformation, glm::vec3(xBoatPos, yBoatPos, 0.0f));

	//oteksturowana czêœæ ³ódki
	shader.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.get_programID(), "Texture0"), 0);
    
	//pobranie lokalizacji zmiennych w progamie shadera
	GLint viewLoc = glGetUniformLocation(shader.get_programID(), "view");
	GLint projLoc = glGetUniformLocation(shader.get_programID(), "projection");
	GLuint modelLoc = glGetUniformLocation(shader.get_programID(), "model");
	GLuint transLoc = glGetUniformLocation(shader.get_programID(), "transformation");
	//wys³anie macierzy pod odpowiednie lokalizacje
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transformation));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//bia³a góra
	shader2.Use();

	viewLoc = glGetUniformLocation(shader2.get_programID(), "view");
	projLoc = glGetUniformLocation(shader2.get_programID(), "projection");
	modelLoc = glGetUniformLocation(shader2.get_programID(), "model");
	transLoc = glGetUniformLocation(shader2.get_programID(), "transformation");
	//wys³anie macierzy pod odpowiednie lokalizacje
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transformation));

	glBindVertexArray(VAO2);
	glDrawElements(GL_TRIANGLES, indices2.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}