#include "DrawTools.h"

void drawCircle(double x, double y, float r)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, r * 5, r * 5);
    glPopMatrix();
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