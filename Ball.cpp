#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include <iostream>

#include "DrawTools.cpp"
#include "BaseTypes.cpp"

class Ball {
    public:
	Vector location;

public:
	Vector speed = Vector(0, 0);

public:
    Ball(int x, int y) : location(x, y) {}

	void drawBall(void)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		drawCircle(location.x, location.y, 20);
		glColor3f(0.0f, 0.0f, 0.9f);
		drawCircle(location.x, location.y, 15);
	}

    void move() {

    }

};