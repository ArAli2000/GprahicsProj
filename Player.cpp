#include <stdlib.h>
#include <cmath>
#ifdef _WIN32
#include <glut.h>
#else
#include <GL/glut.h>
#endif
#include "Ball.h"
#include "DrawTools.h"
#include "Player.h"

Player::Player(double x, double y) : location(x, y){};

void Player::drawPlayer1(void)
{
	updateLocation();
	glColor3f(0.0f, 0.589f, 0.222f);
	drawCircle(location.x, location.y, radius);
	glColor3f(0.992f, 0.863f, 0.0f);
	drawCircle(location.x, location.y, 6*radius / 10);
	glColor3f(0.0f, 0.128f, 0.410f);
	drawCircle(location.x, location.y, 4*radius / 10);
}

void Player::drawPlayer2(void)
{
	updateLocation();
	glColor3f(0.86f, 0.0f, 0.0f);
	drawCircle(location.x, location.y, radius);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawCircle(location.x, location.y, 6*radius / 10);
	glColor3f(1.0f, 0.796f, 0.0f);
	drawCircle(location.x, location.y, 4*radius / 10);
}

void Player::move(double x, double y)
{
	if (x > 0)
	{
		speed.x = movementSpeed;
	}
	else if (x == 0)
	{
		speed.x = 0;
	}
	else
	{
		speed.x = -1 * movementSpeed;
	}
	if (y > 0)
	{
		speed.y = movementSpeed;
	}
	else if (y == 0)
	{
		speed.y = 0;
	}
	else
	{
		speed.y = -1 * movementSpeed;
	}
}

void Player::bound(Vector &boundDirections, double safeX, double safeY)
{
	isBounded = true;
	boundDirection = boundDirections;
	if (boundDirections.y)
	{
		safeLocation.y = safeY;
		speed.y = 0;
	}
	if (boundDirections.x)
	{
		safeLocation.x = safeX;
		speed.x = 0;
	}
}

void Player::fixCollision()
{
	if (boundDirection.y)
	{
		location.y = safeLocation.y;
	}
	if (boundDirection.x)
	{
		location.x = safeLocation.x;
	}
	
}

void Player::updateLocation()
{
	if (speed.x || speed.y)
	{
		location.x += speed.x;
		location.y += speed.y;
	}
	if (isBounded)
	{
		fixCollision();
		isBounded = false;
	}
}

CircleBorder Player::getPlayerBorder() {
	return CircleBorder(location, radius, speed);
}
