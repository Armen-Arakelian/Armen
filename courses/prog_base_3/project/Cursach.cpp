#include "stdafx.h"
#include <stdio.h>
#include <GL/glut.h>

int WindW, WindH;
int i;
int alpha;

void Reshape(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 100, 100, 100);

	WindW = width;
	WindH = height;
}

void Display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(3);
	glColor3f(0.0f, 0.6f, 0.9f);

	glPushMatrix();
	glRotatef(alpha, alpha, 0.0f, 1.0f);
	alpha += 5;
	if (alpha > 359) 
		alpha = 0;
	glBegin(GL_LINES);
	glVertex3f(-0.5f, 0.5f, 0.7f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.2f, 0.2f, 0.3f);
	glVertex3f(0.2f, -0.2f, 0.4f);
	glVertex3f(-0.1f, 0.1f, 0.15f);
	glVertex3f(0.1f, -0.1f, 0.2f);
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
	alpha = 0;

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
