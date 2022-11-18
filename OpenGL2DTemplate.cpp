#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <list>
#include <string>

#include "Ball.h"
#include "DrawTools.h"
#include "controls.cpp"
#include "Player.h"
#include "Collision.cpp"

void Display(void);
void Anim(void);

const int period = 10;

float xr, yr, xrP2, yrP2 = 0;
int frame = 0, timebase = 0;
int fps = 0;

void testCallback();

Player p1(250, 445);
Player p2(250, 55);
Ball b(0, 0);
controls c;

CollisionCase c1({CircleBorder(Vector(3, 5), 3)}, &testCallback);
CollisionDetector cd;

void testCallback()
{
	printf("This is a callback");
}

void testCollision()
{
	CircleBorder p1B(p1.location, 20);
	// RectangleBorder rB(Vector(60, 40), Vector(440, 460));
	CircleBorder p2B(p2.location, 20);
	bool collision = cd.circleCircleCollisionDetect(p1B, p2B);

	if (collision)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		drawCircle(250, 250, 48);
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	c.keyPressed(key, x, y);
}

void keyUp(unsigned char key, int x, int y)
{
	c.keyUp(key, x, y);
}

void keyOperations()
{
	c.keyOperations(p2);
	c.keyOperations2(p1);
}

void timer(int n)
{
	keyOperations();

	glutPostRedisplay();
	glutTimerFunc(period, timer, 0);

	frame++;
	long time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > period)
	{
		fps = frame * 1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		std::cout << fps;
		std::cout << ' ';
	}
}

void refreshScreen()
{
	frame++;
	long time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > period)
	{
		glutPostRedisplay();
		fps = frame * 1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		std::cout << fps;
		std::cout << ' ';
	}
}

int main(int argc, char **argr)
{
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Shape");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glutDisplayFunc(Display);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutIgnoreKeyRepeat(0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(period, timer, 0);

	// glutIdleFunc(refreshScreen);
	glutMainLoop();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.25f, 0.25f, 0.45f);
	glRectf(30.0f, 10.0f, 470.0f, 490.0f);

	glColor3f(0.7f, 0.225f, 0.12f);
	glRectf(60.0f, 40.0f, 440.0f, 460.0f);

	glColor3f(1, 1, 1);
	drawCircle(250, 250, 50);

	glColor3f(0.7f, 0.225f, 0.12f);
	drawCircle(250, 250, 48);

	glColor3f(1, 1, 1);
	drawCircle(250, 250, 3);

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(60, 250);
	glVertex2f(440, 250);
	glEnd();

	p1.drawPlayer();
	p2.drawPlayer();
	b.drawBall();
	testCollision();

	glFlush();
}

void Anim()
{
}
