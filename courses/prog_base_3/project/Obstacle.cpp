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

void Obstacle::spawnObstacle()
{
	glBegin(GL_QUADS);
	int r = rand() % 100;
	double z = r / 10;
	switch (l)
	{
	case RIGHT :
		glVertex3f(2.2f, 0.0f, z);
		glVertex3f(2.2f, 0.5f, z);
		glVertex3f(1.6f, 0.0f, z);
		glVertex3f(1.6f, 0.5f, z);
		break;
	case MIDDLE :
		glVertex3f(1.5f, 0.0f, z);
		glVertex3f(1.5f, 0.5f, z);
		glVertex3f(0.6f, 0.0f, z);
		glVertex3f(0.6f, 0.5f, z);
		break;
	case LEFT :
		glVertex3f(0.5f, 0.0f, z);
		glVertex3f(0.5f, 0.5f, z);
		glVertex3f(-0.2f, 0.0f, z);
		glVertex3f(-0.2f, 0.5f, z);
		break;
	}
	glEnd();
}