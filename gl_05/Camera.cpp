#include "Camera.h"

Camera::Camera()
{
	rot_angle = 0.0f;  //k¹t obrotu wyra¿ony w stopniach

	cameraX = -3.0f;  //wspó³rzêdna x po³o¿enia kamery
	cameraHeight = 1.0f;  //wysokoœæ z której obserwujemy scenê (wspó³rzêdna y po³o¿enia kamery)
	cameraZ = -3.0f;  //wspó³rzêdna z po³o¿enia kamery

	watchedPointX = 0.0f;  //wspó³rzêdna x punktu na który skierowana jest kamera
	watchedPointY = 0.0f;  //wspó³rzêdna y punktu na który skierowana jest kamera
	watchedPointZ = 0.0f;  //wspó³rzêdna z punktu na który skierowana jest kamera
}

void Camera::rotRight()
{
	rot_angle += 2.0f;  //zmiana k¹tu obrotu
	if (rot_angle >= 360.0f)
		rot_angle -= 360.0f;
}

void Camera::rotLeft()
{
	rot_angle -= 2.0f;  //zmiana k¹tu obrotu
	if (rot_angle < 0.0f)
		rot_angle += 360.0f;
}

void Camera::rotDown()
{
	cameraHeight -= 0.1f;
}

void Camera::rotUp()
{
	cameraHeight += 0.1f;
}

void Camera::moveForward()
{
	GLfloat xSegment = (watchedPointX - cameraX);
	GLfloat zSegment = (watchedPointZ - cameraZ);

	watchedPointX += xSegment / STEP;
	watchedPointZ += zSegment / STEP;
	cameraX += xSegment / STEP;
	cameraZ += zSegment / STEP;
}

void Camera::moveBackward()
{
	GLfloat xSegment = (watchedPointX - cameraX);
	GLfloat zSegment = (watchedPointZ - cameraZ);

	watchedPointX -= xSegment / STEP;
	watchedPointZ -= zSegment / STEP;
	cameraX -= xSegment / STEP;
	cameraZ -= zSegment / STEP;
}

void Camera::moveRight()
{
	GLfloat xSegment = (watchedPointX - cameraX);
	GLfloat zSegment = (watchedPointZ - cameraZ);
	GLfloat cameraPointSegment = sqrt((watchedPointX - cameraX) * (watchedPointX - cameraX) + (watchedPointZ - cameraZ) * (watchedPointZ - cameraZ));
	GLfloat sinusAlfa = (watchedPointX - cameraX) / (cameraPointSegment);

	if (sinusAlfa < 0.5 && sinusAlfa > -0.5)
	{
		GLfloat a2 = (watchedPointX - cameraX) / (cameraZ - watchedPointZ);
		GLfloat b2 = cameraZ - a2 * cameraX;
		GLfloat Xmovement = 0.1;

		if (watchedPointZ < cameraZ)
		{
			cameraX += Xmovement;
		}
		else
		{
			cameraX -= Xmovement;
		}
		cameraZ = a2 * cameraX + b2;
		watchedPointX = cameraX + xSegment;
		watchedPointZ = cameraZ + zSegment;
	}
	else
	{
		GLfloat a2 = (watchedPointZ - cameraZ) / (cameraX - watchedPointX);
		GLfloat b2 = cameraX - a2 * cameraZ;
		sinusAlfa = (watchedPointZ - cameraZ) / (cameraPointSegment);
		GLfloat Zmovement = 0.1;

		if (watchedPointX > cameraX)
		{
			cameraZ += Zmovement;
		}
		else
		{
			cameraZ -= Zmovement;
		}
		cameraX = a2 * cameraZ + b2;
		watchedPointX = cameraX + xSegment;
		watchedPointZ = cameraZ + zSegment;
	}
}

void Camera::moveLeft()
{
	GLfloat xSegment = (watchedPointX - cameraX);
	GLfloat zSegment = (watchedPointZ - cameraZ);
	GLfloat cameraPointSegment = sqrt((watchedPointX - cameraX) * (watchedPointX - cameraX) + (watchedPointZ - cameraZ) * (watchedPointZ - cameraZ));
	GLfloat sinusAlfa = (watchedPointX - cameraX) / (cameraPointSegment);

	if (sinusAlfa < 0.5 && sinusAlfa > -0.5)
	{
		GLfloat a2 = (watchedPointX - cameraX) / (cameraZ - watchedPointZ);
		GLfloat b2 = cameraZ - a2 * cameraX;
		GLfloat Xmovement = 0.1;

		if (watchedPointZ < cameraZ)
		{
			cameraX -= Xmovement;
		}
		else
		{
			cameraX += Xmovement;
		}
		cameraZ = a2 * cameraX + b2;
		watchedPointX = cameraX + xSegment;
		watchedPointZ = cameraZ + zSegment;
	}
	else
	{
		GLfloat a2 = (watchedPointZ - cameraZ) / (cameraX - watchedPointX);
		GLfloat b2 = cameraX - a2 * cameraZ;
		sinusAlfa = (watchedPointZ - cameraZ) / (cameraPointSegment);
		GLfloat Zmovement = 0.1;

		if (watchedPointX > cameraX)
		{
			cameraZ -= Zmovement;
		}
		else
		{
			cameraZ += Zmovement;
		}
		cameraX = a2 * cameraZ + b2;
		watchedPointX = cameraX + xSegment;
		watchedPointZ = cameraZ + zSegment;
	}
}

void Camera::moveUp()
{
	cameraHeight += 0.1f;
	watchedPointY += 0.1f;
}

void Camera::moveDown()
{
	cameraHeight -= 0.1f;
	watchedPointY -= 0.1f;
}

void Camera::setMatrixes(const GLuint WIDTH, const GLuint HEIGHT)
{
	glm::mat4 camRot;
	camRot = translate(camRot, glm::vec3(watchedPointX, watchedPointY, watchedPointZ));
	camRot = glm::rotate(camRot, glm::radians(rot_angle), glm::vec3(0.0, 1.0, 0.0));
	camRot = translate(camRot, glm::vec3((-1) * watchedPointX, (-1) * watchedPointY, (-1) * watchedPointZ));
	glm::vec3 cameraPos = glm::vec3(camRot * glm::vec4(cameraX, cameraHeight, cameraZ, 1.0f)); //pocz¹tkowe po³o¿enie kamery

	cameraX = cameraPos.x;
	cameraHeight = cameraPos.y;
	cameraZ = cameraPos.z;
	rot_angle = 0;

	view = glm::lookAt(cameraPos, glm::vec3(watchedPointX, watchedPointY, watchedPointZ), glm::vec3(0.0f, 1.0f, 0.0f));  //przesuniêcie obserwatora o 3 jednostki do ty³u
	//macierz rzutowania - macierz rzutu perspektywicznego, parametry: k¹t widzenia, aspekt, zNear, zFar
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Camera::getView()
{
	return view;
}

glm::mat4 Camera::getProjection()
{
	return projection;
}