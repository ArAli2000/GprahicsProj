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

private:
	int movementSpeed = 8;

public:
	Player(int x, int y) : location(x, y){};

	void drawPlayer(void)
	{
		updateLocation();
		glColor3f(0.0f, 0.0f, 1.0f);
		drawCircle(location.x, location.y, 20);
		glColor3f(0.0f, 0.0f, 0.9f);
		drawCircle(location.x, location.y, 15);
		glColor3f(0.0f, 0.0f, 0.8f);
		drawCircle(location.x, location.y, 5);
	}

	void move(int x, int y) {
		if (x > 0) {
			speed.x = movementSpeed;
		} else if (x == 0) {
			speed.x = 0;
		} else {
			speed.x = -1*movementSpeed;
		}
		if (y > 0) {
			speed.y = movementSpeed;
		} else if (y == 0) {
			speed.y = 0;
		} else {
			speed.y = -1*movementSpeed;
		}
	}

	void updateLocation()
	{
		location.x += speed.x;
		location.y += speed.y;
	}
};
