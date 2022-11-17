#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>

#include "Player.cpp"

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
		if (keystates['w'])
		{
			p.speed.y = 8;
		}
		if (keystates['s'])
		{
			p.speed.y = -8;
		}

		if (keystates['w'] == keystates['s'])
		{
			p.speed.y = 0;
		}

		if (keystates['a'])
		{
			p.location.x -= 8;
		}
		if (keystates['d'])
		{

			p.location.x += 8;
		}

		if (keystates['a'] == keystates['d'])
		{
			p.speed.x = 0;
		}
	}

	void keyOperations2(Player &p)
	{
		if (keystates['i'])
		{
			p.speed.y = 15;
		}
		if (keystates['k'])
		{
			p.speed.y = -15;
		}
		if (keystates['i'] == keystates['k'])
		{
			p.speed.y = 0;
		}
		if (keystates['l'])
		{
			p.speed.x = 15;
		}
		if (keystates['j'])
		{
			p.speed.x = -15;
		}
		if (keystates['l'] == keystates['j'])
		{
			p.speed.x = 0;
		}
	}
};