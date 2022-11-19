#include <iostream>
#include <cmath>
#ifdef _WIN32
#include <glut.h>
#else
#include <GL/glut.h>
#endif
#include <list>
#include <string>
#include <Windows.h>

#include "Ball.h"
#include "DrawTools.h"
#include "controls.cpp"
#include "Player.h"
#include "Collision.cpp"

void Display(void);
void Anim(void);
void Init(int *argc, char **arg);

const int period = 10;
const int wX = 500;
const int wY = 500;
const char *WindowName = "Our Game";

float xr, yr, xrP2, yrP2 = 0;
int frame = 0, timebase = 0;
int fps = 0;

void testCallback();

Player p1(250, 420);
Player p2(250, 55);
Ball b(250, 350);
controls c;

// CollisionCase c1({CircleBorder(Vector(3, 5), 3)}, &testCallback);
Vector start(60, 460);
Vector end(440, 40);
int thickness = 5;
RectangleBorder rb = RectangleBorder(start, end);
RectangleBorder rbDown = RectangleBorder(Vector(start.x, end.y), Vector(end.x, 0));
RectangleBorder rbLeft = RectangleBorder(Vector(0, wX), Vector(start.x, 0));
RectangleBorder rbRight = RectangleBorder(Vector(end.x, wY), Vector(wX, 0));
RectangleBorder rbUp = RectangleBorder(Vector(start.x, wX), Vector(end.x, start.y));
RectangleBorder rbMid = RectangleBorder(Vector(0, ((start.y + end.y) / 2.0) + thickness), Vector(wX, ((start.y + end.y) / 2.0) - thickness));
CircleBorder p1Border = p1.getPlayerBorder();
CircleBorder p2Border = p2.getPlayerBorder();
CircleBorder ballBorder = b.getBallBorder();

std::list<Border *> p1Bounds = {
	&p1Border,
	&rbUp,
	&rbRight,
	&rbLeft,
	&rbMid,
};

std::list<Border *> p2Bounds = {
	&p2Border,
	&rbDown,
	&rbRight,
	&rbLeft,
	&rbMid,
};

std::list<Border *> ballP1Touch = {
	&ballBorder,
	&p1Border,
};

std::list<Border *> ballP2Touch = {
	&ballBorder,
	&p2Border,
};

std::list<Border *> ballBounds = {
	&ballBorder,
	&rbUp,
	&rbDown,
	&rbLeft,
	&rbRight,
};

std::list<Border *> l1 = {
	&p1Border,
	&rb,
};

std::list<Border *> l2 = {
	&p2Border,
	&rb,
};

void p1Callback(Vector &boundDirections, double safeX, double safeY)
{
	p1.bound(boundDirections, safeX + p1.radius * boundDirections.x, safeY + p1.radius * boundDirections.y);
}

void p2Callback(Vector &boundDirections, double safeX, double safeY)
{
	p2.bound(boundDirections, safeX + p2.radius * boundDirections.x, safeY + p2.radius * boundDirections.y);
}

void ballTouchCallback(Vector &incomingSpeed, double touchX, double touchY)
{
	b.collideWithCircle(incomingSpeed, touchX, touchY);
	printf("Touch Ball");
};

void ballBoundCallback(Vector &directionVector, double safeX, double safeY)
{
	b.collideWithRect(directionVector, safeX, safeY);
	printf("Bound Ball");
}

CollisionDetector cd({
	CollisionCase(p1Bounds, p1Callback),
	CollisionCase(p2Bounds, p2Callback),
	CollisionCase(ballP1Touch, ballTouchCallback),
	CollisionCase(ballP2Touch, ballTouchCallback),
	CollisionCase(ballBounds, ballBoundCallback),
});

void testCallback()
{
	printf("This is a callback");
}

// void testCollision()
// {
// 	CircleBorder p1B(p1.location, 20);
// 	RectangleBorder rB(Vector(60, 40), Vector(440, 460));
// 	CircleBorder p2B(p2.location, 20);
// 	Collision collision = cd.circleRectCollisionDetect(p1B, rB, p1.speed);

// 	if (collision)
// 	{
// 		p1.bound(collision.direction, collision.collisionPoint.x + 20*collision.direction.x, collision.collisionPoint.y + 20*collision.direction.y);
// 	}
// }

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
		// std::cout << fps;
		// std::cout << ' ';
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
	Init(&argc, argr);
	glutDisplayFunc(Display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(period, timer, 0);
	glutMainLoop();
}

void Init(int *argc, char **arg)
{
	glutInit(argc, arg);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(wX, wY);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(WindowName);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutIgnoreKeyRepeat(0);
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

	// testCollision();
	// rbDown.drawRectangle(1,0,0);
	// rbLeft.drawRectangle(0,1,0);
	// rbRight.drawRectangle(0,1,0);
	// rbUp.drawRectangle(1,0,0);
	// rbMid.drawRectangle(0, 0, 1);
	cd.detectCollisions();
	b.drawBall();
	p1.drawPlayer();
	p2.drawPlayer();

	glutSwapBuffers();
}

void Anim()
{
}
