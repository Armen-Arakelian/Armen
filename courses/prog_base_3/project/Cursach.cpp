#include "stdafx.h"
#include <GL/glut.h>

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(1);

	glBegin(GL_LINES);
	glVertex3f(0, 0.5f, 1);
	glVertex3f(0, -0.5f, 1);
	glEnd();

	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("gbtrbb");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glClearColor(0, 0, 0, 0);

	glutMainLoop();
	return 0;
}