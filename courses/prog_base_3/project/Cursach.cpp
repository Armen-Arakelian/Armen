#include "stdafx.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "Obstacle.h"

int WindW, WindH;
int i;
double alphaR = 0;
double alphaL = 0;
double alphaM = 0;
double beta = 0.02;

void Reshape(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(130, 1, 50, 0);
	gluLookAt(1.0, 2.0, 2.0, 1.0, 1.5, -10.0, 0.0, 1.0, 0.0);

	WindW = width;
	WindH = height;
}

void Display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3);
	glColor3f(0.0f, 0.6f, 0.9f);

	glPushMatrix();
	glTranslatef(0, 0, alphaR);
	alphaR += beta;
	if (alphaR > 1)
	{
		alphaR = rand() % 9;
		alphaR = alphaR / 10;
	}
	Obstacle * ob1 = new Obstacle(RIGHT);
	ob1->spawnObstacle();

	glTranslatef(0, 0, alphaM);
	alphaM += beta;
	if (alphaM > 1)
	{
		alphaM = rand() % 9;
		alphaM = alphaM / 10;
	}
	Obstacle * ob2 = new Obstacle(MIDDLE);
	ob2->spawnObstacle();

	glTranslatef(0, 0, alphaL);
	alphaL += beta;
	if (alphaL > 1)
	{
		alphaL = rand() % 9;
		alphaL = alphaL / 10;
	}
	Obstacle * ob3 = new Obstacle(LEFT);
	ob3->spawnObstacle();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(2.0f, 0.5f, 0.0f);
	glVertex3f(2.0f, 0.5f, 100.0f);
	glVertex3f(1.4f, 0.5f, 0.0f);
	glVertex3f(1.4f, 0.5f, 100.0f);
	glVertex3f(0.7f, 0.5f, 0.0f);
	glVertex3f(0.7f, 0.5f, 100.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 100.0f);
	glEnd();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void Visibility(int state) 
{
	if (state == GLUT_NOT_VISIBLE) printf("Window not visible!\n");
	if (state == GLUT_VISIBLE) printf("Window visible!\n");
}

void timf(int value) 
{
	glutPostRedisplay();  
	glutTimerFunc(40, timf, 0); 
}

int main(int argc, char *argv[])
{
	WindW = 400;
	WindH = 300;

	glutInit(&argc, argv);
	glutInitWindowSize(WindW, WindH);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("buiviuh");

	glutReshapeFunc(Reshape); 
	glutDisplayFunc(Display);    
	glutTimerFunc(40, timf, 0); 
	glutVisibilityFunc(Visibility); 
	glClearColor(0, 0, 0, 0);

	glutMainLoop();

	return 0;
}
