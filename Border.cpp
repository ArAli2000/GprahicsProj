#include "BaseTypes.h"
#include "Border.h"
#include "DrawTools.h"

bool Border::operator==(const Border& lhs)
{
    return lhs.shape == shape;
}
double Border::getCircleRadius() {
    return 0;
}
Vector Border::getCircleVelocity() {
    return Vector(0,0);
}
Vector Border::getCircleLocation() {
    return Vector(0,0);
}
Vector Border::getRectangleTopLeft(){
    return Vector(0,0);
}

Vector Border::getRectangleBottomRight(){
    return Vector(0,0);
}


CircleBorder::CircleBorder(Vector &location, double r, Vector &velocity) : location(&location), velocity(&velocity)
{
    this->shape = BorderShape::circle;
    this->r = r;
}

double CircleBorder::getCircleRadius() {
    return r;
}
Vector CircleBorder::getCircleVelocity() {
    return *velocity;
}
Vector CircleBorder::getCircleLocation() {
    return *location;
}

RectangleBorder::RectangleBorder(Vector &topLeft, Vector &bottomRight) : topLeft(topLeft), bottomRight(bottomRight)
{
    this->shape = BorderShape::rectangle;
}

RectangleBorder::RectangleBorder(const Vector &topLeft, Vector &bottomRight) : topLeft(topLeft), bottomRight(bottomRight)
{
    this->shape = BorderShape::rectangle;
}

RectangleBorder::RectangleBorder(Vector &topLeft, const Vector &bottomRight) : topLeft(topLeft), bottomRight(bottomRight)
{
    this->shape = BorderShape::rectangle;
}

RectangleBorder::RectangleBorder(const Vector &topLeft, const Vector &bottomRight) : topLeft(topLeft), bottomRight(bottomRight)
{
    this->shape = BorderShape::rectangle;
}

void RectangleBorder::drawRectangle(double r, double g, double b) {
    glColor3f(r, g, b);
    glRectf(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}

Vector RectangleBorder::getRectangleTopLeft() {
    return topLeft;
}
Vector RectangleBorder::getRectangleBottomRight() {
    return bottomRight;
}
