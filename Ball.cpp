#include <stdlib.h>
#include <cmath>
#ifdef WIN32
#include <glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

#include "DrawTools.h"
#include "BaseTypes.h"
#include "Ball.h"

Ball::Ball(int x, int y) : location(x, y) {}

void Ball::drawBall(void)
{
	updateLocation();
	glColor3f(0.0f, 0.0f, 1.0f);
	drawCircle(location.x, location.y, 10);
	glColor3f(0.0f, 0.0f, 0.9f);
	drawCircle(location.x, location.y, 5);
}

void Ball::applyFriction()
{
	double xDir = 0;
	double yDir = 0;

	if (speed.x > 0)
	{
		xDir = 1;
	}
	else if (speed.x < 0)
	{
		xDir = -1;
	}

	if (speed.y > 0)
	{
		yDir = 1;
	}
	else if (speed.y < 0)
	{
		yDir = -1;
	}
	speed.x -= friction * xDir;
	speed.y -= friction * yDir;
}

void Ball::updateLocation()
{
	if (speed.x || speed.y)
	{
		applyFriction();
		location.x += speed.x;
		location.y += speed.y;
	}
}
