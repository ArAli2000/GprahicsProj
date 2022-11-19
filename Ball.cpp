#include <stdlib.h>
#include <cmath>
#ifdef _WIN32
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
	drawCircle(location.x, location.y, radius);
	glColor3f(0.0f, 0.0f, 0.9f);
	drawCircle(location.x, location.y, (2 * radius) / 3);
}

void Ball::applyFriction()
{
	double xDir = speed.x / abs(speed.x);
	double yDir = speed.y / abs(speed.y);

	double xFriction = friction * xDir;
	double yFriction = friction * yDir;

	if (abs(speed.x) - friction < 0)
	{
		xFriction = speed.x;
	}

	if (abs(speed.y) - friction < 0)
	{
		yFriction = speed.y;
	}

	speed.x -= xFriction;
	speed.y -= yFriction;
}

void Ball::updateLocation()
{
	if (speed.x || speed.y)
	{
		applyFriction();
	}
	if (collided)
	{
		fixCollision();
		collided = false;
	}
	location.x += speed.x;
	location.y += speed.y;
}

CircleBorder Ball::getBallBorder()
{
	return CircleBorder(location, radius, speed);
}

void Ball::fixCollision()
{
	location.x = touchLocation.x;
	location.y = touchLocation.y;
	speed.x = collideSpeed.x;
	speed.y = collideSpeed.y;
}

void Ball::collideWithRect(Vector &directionVector, double safeX, double safeY)
{

	touchLocation.x = safeX + (radius)*directionVector.x;
	touchLocation.y = safeY + (radius)*directionVector.y;

	int xDir = -1;
	int yDir = -1;
	if (directionVector.x == 0)
	{
		xDir = 1;
	}
	if (directionVector.y == 0)
	{
		yDir = 1;
	}

	collideSpeed.x = speed.x * xDir;
	collideSpeed.y = speed.y * yDir;
	collided = true;
}

void Ball::collideWithCircle(Vector &incomingSpeed, double touchX, double touchY)
{
	int xDir = 1;
	int yDir = 1;

	Vector directionVector = Vector(location.x - touchX, location.y - touchY);
	if (directionVector.x < 0)
	{ // Ball to the left
		xDir = -1;
	}

	if (directionVector.y < 0)
	{ // Ball below
		yDir = -1;
	}

	touchLocation.x = touchX + (radius)*xDir;
	touchLocation.y = touchY + (radius)*yDir;

	Vector reboundSpeed = Vector(abs(incomingSpeed.x - speed.x), abs(incomingSpeed.y - speed.y));
	double magnitude = sqrt(pow(reboundSpeed.x, 2) + pow(reboundSpeed.y, 2));
	double angle = atan((directionVector.y / directionVector.x));

	double degree = (angle * 180) / (22 / 7);
	collideSpeed.x = magnitude * cos(angle) * xDir;
	collideSpeed.y = magnitude * sin(abs(angle)) * (yDir);
	collided = true;
}
