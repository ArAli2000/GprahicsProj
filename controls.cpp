#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>

#include "Player.h"

class controls
{
	bool keystates[256] = {false};

public:
	controls()
	{
	}

	void keyPressed(unsigned char key, int x, int y)
	{
		keystates[key] = true;
	}

	void keyUp(unsigned char key, int x, int y)
	{
		keystates[key] = false;
	}

	void keyOperations(Player &p)
	{
		int yDir;
		int xDir;

		if (keystates['w'])
		{
			yDir = 1;
		}
		if (keystates['s'])
		{
			yDir = -1;
		}

		if (keystates['w'] == keystates['s'])
		{
			yDir = 0;
		}

		if (keystates['a'])
		{
			xDir = -1;
		}
		if (keystates['d'])
		{

			xDir = 1;
		}

		if (keystates['a'] == keystates['d'])
		{
			xDir = 0;
		}

		p.move(xDir, yDir);
	}

	void keyOperations2(Player &p)
	{

		int yDir;
		int xDir;
		if (keystates['i'])
		{
			yDir = 1;
		}
		if (keystates['k'])
		{
			yDir = -1;
		}
		if (keystates['i'] == keystates['k'])
		{
			yDir = 0;
		}
		if (keystates['l'])
		{
			xDir = 1;
		}
		if (keystates['j'])
		{
			xDir = -1;
		}
		if (keystates['l'] == keystates['j'])
		{
			xDir = 0;
		}

		p.move(xDir, yDir);
	}
};