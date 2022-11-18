#include "DrawTools.h"

void drawCircle(int x, int y, float r)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, r*5, r*5);
    glPopMatrix();
}