#include <stdlib.h> 
#include <cmath>
#include <glut.h>

#include "Player.cpp"

class controls {
	bool keystates[256] = { false };
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
				if (p.yr < 0)
				{
					p.yr += 8;
				}
			}
			if (keystates['s'])
			{
				if (p.yr > -185)
				{
					p.yr -= 8;
				}
			}
			if (keystates['a'])
			{
				if (p.xr > -164)
				{
					p.xr -= 8;
				}
			}
			if (keystates['d'])
			{
				if (p.xr < 164)
				{
					p.xr += 8;
				}
			}
		}
	void keyOperations2(Player& p)
	{
		if (keystates['i'])
		{
			if (p.yr + 15 > 190)
			{
				p.yr = 190;
				glutPostRedisplay();
			}
			if (p.yr < 190)
			{
				p.yr += 15;
				glutPostRedisplay();
			}
		}
		if (keystates['k'])
		{
			if (p.yr - 15 < 0)
			{
				p.yr = 0;
				glutPostRedisplay();
			}
			if (p.yr > 0)
			{
				p.yr -= 15;
				glutPostRedisplay();
			}
		}
		if (keystates['l'])
		{
			if (p.xr + 15 > 170)
			{
				p.xr = 170;
				glutPostRedisplay();
			}
			if (p.xr < 170)
			{
				p.xr += 15;
				glutPostRedisplay();
			}
		}
		if (keystates['j'])
		{
			if (p.xr - 15 < -170)
			{
				p.xr = -170;
				glutPostRedisplay();
			}
			if (p.xr > -170)
			{
				p.xr -= 15;;
				glutPostRedisplay();
			}
		}
	}
	
};