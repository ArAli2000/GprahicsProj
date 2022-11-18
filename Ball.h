#ifndef BALL_H
#define BALL_H
#include "BaseTypes.h"

class Ball {
    public:
	Vector location;

public:
	Vector speed = Vector(20, 20);

private:
	double friction = 0.5;

public:
    Ball(int x, int y);

	void drawBall(void);

	void applyFriction();

    void updateLocation();
};

#endif