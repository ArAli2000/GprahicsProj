#include "TextureBuilder.h"
#include <iostream>
#include <cmath>
#ifdef _WIN32
#include <glut.h>
#else
#include <GL/glut.h>
#endif
#include <list>
#include "Game.cpp"
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
void onMouseClick(int button, int state, int x, int y);
GLuint LoadTexture(const char *filename);

const int period = 10;
const int wX = 500;
const int wY = 600;
const int fix = 200;
const char *WindowName = "Our Game";

GLuint texture;

float xr, yr, xrP2, yrP2 = 0;
int frame = 0, timebase = 0;
int fps = 0;

void testCallback();

Player p1(250, 530);
Player p2(250, 70);
Ball b(250, 300);
controls c;
Game g;

// CollisionCase c1({CircleBorder(Vector(3, 5), 3)}, &testCallback);
Vector start(22.5, 562.5);
Vector end(477.5, 37.5);

Vector goal(((start.x + end.x) / 2) - ((end.x - start.x)) * 0.0901, ((start.x + end.x) / 2) + ((end.x - start.x)) * 0.0901);

int thickness = 5;
RectangleBorder rb = RectangleBorder(start, end);
RectangleBorder rbDown = RectangleBorder(Vector(-fix, end.y), Vector(wX + fix, -fix));
RectangleBorder rbLeft = RectangleBorder(Vector(-fix, wY + fix), Vector(start.x, -fix));
RectangleBorder rbRight = RectangleBorder(Vector(end.x, wY + fix), Vector(wX + fix, -fix));
RectangleBorder rbUp = RectangleBorder(Vector(-fix, wY + fix), Vector(wX + fix, start.y));
RectangleBorder rbMid = RectangleBorder(Vector(0, ((start.y + end.y) / 2.0) + thickness), Vector(wX, ((start.y + end.y) / 2.0) - thickness));
RectangleBorder goalDown = RectangleBorder(Vector(goal.x, end.y), Vector(goal.y, -fix));
RectangleBorder goalUp = RectangleBorder(Vector(goal.x, wY + fix), Vector(goal.y, start.y));
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

std::list<Border *> goalDownBound = {
	&ballBorder,
	&goalDown,
};

std::list<Border *> goalUpBound = {
	&ballBorder,
	&goalUp,
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
};

void ballBoundCallback(Vector &directionVector, double safeX, double safeY)
{
	b.collideWithRect(directionVector, safeX, safeY);
}

void goalBoundUpCallback(Vector &directionVector, double safeX, double safeY)
{
	g.player1Scored();
}

void goalBoundDownCallback(Vector &directionVector, double safeX, double safeY)
{
	g.player2Scored();
}

CollisionDetector cd({
	CollisionCase(p1Bounds, p1Callback),
	CollisionCase(p2Bounds, p2Callback),
	CollisionCase(ballP1Touch, ballTouchCallback),
	CollisionCase(ballP2Touch, ballTouchCallback),
	CollisionCase(ballBounds, ballBoundCallback),
	CollisionCase(goalDownBound, goalBoundDownCallback),
	CollisionCase(goalUpBound, goalBoundUpCallback),

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
	glutMouseFunc(onMouseClick);
	glutMainLoop();
}

void Init(int *argc, char **arg)
{
	glutInit(argc, arg);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glEnable(GL_TEXTURE_2D);
	glutInitWindowSize(wX, wY);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(WindowName);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	gluOrtho2D(0.0, wX, 0.0, wY);
	glutIgnoreKeyRepeat(0);
	loadBMP(&texture,"Field-BG.bmp", false);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// glColor3f(0.25f, 0.25f, 0.45f);
	// glRectf(30.0f, 10.0f, 470.0f, 490.0f);

	// glColor3f(0.7f, 0.225f, 0.12f);
	// glRectf(60.0f, 40.0f, 440.0f, 460.0f);

	// glColor3f(1, 1, 1);
	// drawCircle(250, 250, 50);

	// glColor3f(0.7f, 0.225f, 0.12f);
	// drawCircle(250, 250, 48);

	// glColor3f(1, 1, 1);
	// drawCircle(250, 250, 3);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0.0f);
	glVertex3f(wX, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(wX, wY, 0);
	glTexCoord2f(0.0f, 1);
	glVertex3f(0, wY, 0);
	glEnd();
	glPopMatrix();
	glColor4f(1, 1, 1, 0.0f);
	glDisable(GL_TEXTURE_2D);

	// glColor3f(1, 1, 1);
	// glBegin(GL_LINES);
	// glVertex2f(60, 250);
	// glVertex2f(440, 250);
	// glEnd();

	// testCollision();
	// rbDown.drawRectangle(1,0,0);
	// rbLeft.drawRectangle(0,1,0);
	// rbRight.drawRectangle(0,1,0);
	// rbUp.drawRectangle(1,0,0);
	// rbMid.drawRectangle(0, 0, 1);
	g.updateObjects(b, p1, p2);
	// goalDown.drawRectangle(1, 0, 0);
	// goalUp.drawRectangle(1, 0, 0);
	cd.detectCollisions();
	b.drawBall();
	p1.drawPlayer1();
	p2.drawPlayer2();

	glColor4f(1, 1, 1, 0.0);

	glutSwapBuffers();
}

void onMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		b.boostMode();
	}
}

void Anim()
{
}
