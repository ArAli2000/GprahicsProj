#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include "Ball.cpp"

class Player
{
public:
	Vector location;

public:
	Vector speed = Vector(0, 0);

public:
	Player(int x, int y) : location(x, y){};

	void drawPlayer(void)
	{
		move();
		glColor3f(0.0f, 0.0f, 1.0f);
		drawCircle(location.x, location.y, 20);
		glColor3f(0.0f, 0.0f, 0.9f);
		drawCircle(location.x, location.y, 15);
		glColor3f(0.0f, 0.0f, 0.8f);
		drawCircle(location.x, location.y, 5);
	}

	void move()
	{
		location.x += speed.x;
		location.y += speed.y;
	}
};
