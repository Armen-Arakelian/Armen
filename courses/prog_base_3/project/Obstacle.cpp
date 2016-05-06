#include "stdafx.h"
#include <stdio.h>
#include <GL/glut.h>
#include "Obstacle.h"


Obstacle::Obstacle(line _l)
{
	l = _l;
}


Obstacle::~Obstacle()
{
}

int r = rand() % 100;
double z = r / 10;

void Obstacle::spawnObstacle()
{
	glBegin(GL_QUADS);
	switch (l)
	{
	case RIGHT :
		glVertex3f(2.2f, 0.0f, -0.8f);
		glVertex3f(2.2f, 0.5f, -0.8f);
		glVertex3f(1.6f, 0.0f, -0.8f);
		glVertex3f(1.6f, 0.5f, -0.8f);
		break;
	case MIDDLE :
		glVertex3f(1.5f, 0.0f, -1.0f);
		glVertex3f(1.5f, 0.5f, -1.0f);
		glVertex3f(0.6f, 0.0f, -1.0f);
		glVertex3f(0.6f, 0.5f, -1.0f);
		break;
	case LEFT :
		glVertex3f(0.5f, 0.0f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.2f, 0.0f, -0.5f);
		glVertex3f(-0.2f, 0.5f, -0.5f);
		break;
	}
	glEnd();
}