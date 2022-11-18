#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include "Ball.h"
#include "DrawTools.h"
#include "Player.h"


	Player::Player(int x, int y) : location(x, y){};

	void Player::drawPlayer(void)
	{
		updateLocation();
		glColor3f(0.0f, 0.0f, 1.0f);
		drawCircle(location.x, location.y, 20);
		glColor3f(0.0f, 0.0f, 0.9f);
		drawCircle(location.x, location.y, 15);
		glColor3f(0.0f, 0.0f, 0.8f);
		drawCircle(location.x, location.y, 5);
	}

	void Player::move(int x, int y) {
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

	void Player::updateLocation()
	{
		if (speed.x || speed.y) {
			location.x += speed.x;
			location.y += speed.y;
		}
	}
