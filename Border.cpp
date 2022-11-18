#include "BaseTypes.h"
#include "Border.h"

CircleBorder::CircleBorder(const Vector &location, double r) : location(location.x, location.y)
{
    this->shape = BorderShape::circle;
    this->r = r;
}

CircleBorder::CircleBorder(Vector &location, double r) : location(location.x, location.y)
{
    this->shape = BorderShape::circle;
    this->r = r;
}

RectangleBorder::RectangleBorder(Vector &topLeft, Vector &bottomRight) : topLeft(topLeft.x, topLeft.y), bottomRight(bottomRight.x, bottomRight.y)
{
    this->shape = BorderShape::rectangle;
}

RectangleBorder::RectangleBorder(const Vector &topLeft, Vector &bottomRight) : topLeft(topLeft.x, topLeft.y), bottomRight(bottomRight.x, bottomRight.y)
{
    this->shape = BorderShape::rectangle;
}

RectangleBorder::RectangleBorder(Vector &topLeft, const Vector &bottomRight) : topLeft(topLeft.x, topLeft.y), bottomRight(bottomRight.x, bottomRight.y)
{
    this->shape = BorderShape::rectangle;
}

RectangleBorder::RectangleBorder(const Vector &topLeft, const Vector &bottomRight) : topLeft(topLeft.x, topLeft.y), bottomRight(bottomRight.x, bottomRight.y)
{
    this->shape = BorderShape::rectangle;
}
