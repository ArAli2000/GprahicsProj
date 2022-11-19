#ifndef BALL_H
#define BALL_H
#include "BaseTypes.h"
#include "Border.h"

class Ball
{
public:
	Vector location;

public:
	Vector speed = Vector(0, 0);

private:
	double friction = 0.1;

private:
	double radius = 20;

private:
	Vector touchLocation = Vector(0, 0);

private:
	Vector collideSpeed = Vector(0, 0);

private:
	bool collided = false;

public:
	Ball(int x, int y);

	void drawBall(void);

	void applyFriction();

	void updateLocation();

public:
	CircleBorder getBallBorder();

private:
	void fixCollision();

public:
	void collideWithCircle(Vector &incomingSpeed, double touchX, double touchY);

public:
	void collideWithRect(Vector &directionVector, double safeX, double safeY);
};

#endif