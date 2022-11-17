#include <stdlib.h> 
#include <cmath>
#include <glut.h>
#include <iostream>

class Player {
public:int x, y;
public:int xr = 0;
public:int yr = 0;
public:int speed = 0;
public:
	Player(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void drawCircle(int x, int y, float r)
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		GLUquadric* quadObj = gluNewQuadric();
		gluDisk(quadObj, 0, r, 1000, 1000);
		glPopMatrix();
	}


	void drawPlayer(void)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		drawCircle(x + xr, y + yr, 20);
		glColor3f(0.0f, 0.0f, 0.9f);
		drawCircle(x + xr, y + yr, 15);
		glColor3f(0.0f, 0.0f, 0.8f);
		drawCircle(x + xr, y + yr, 5);
	}


};

