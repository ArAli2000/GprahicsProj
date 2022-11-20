#include "DrawTools.h"

void drawCircle(double x, double y, float r)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, r * 5, r * 5);
    glPopMatrix();
}

//this is the method used to print text in OpenGL
//there are three parameters,
//the first two are the coordinates where the text is display,
//the third coordinate is the string containing the text to display
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void drawPointLocation(double x, double y)
{
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(0, y);
    glVertex2f(500, y);
    glEnd();
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(x, 0);
    glVertex2f(x, 500);
    glEnd();
}