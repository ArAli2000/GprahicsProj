#ifndef BORDER_H
#define BORDER_H
#include "BaseTypes.h"

typedef enum
{
    rectangle,
    circle
} BorderShape;

class Border
{
public:
    BorderShape shape;

    bool operator==(const Border &lhs);

public:
    virtual double getCircleRadius();
public:
    virtual Vector getCircleVelocity();
public:
    virtual Vector getCircleLocation();
public:
    virtual Vector getRectangleTopLeft();
public:
    virtual Vector getRectangleBottomRight();
};

class CircleBorder : public Border
{
public:
    double r;

public:
    Vector* location;

public:
    Vector* velocity;

public:
    double getCircleRadius();

public:
    Vector getCircleVelocity();

public:
    Vector getCircleLocation();

public:
    CircleBorder(Vector &location, double r, Vector &velocity);
};

class RectangleBorder : public Border
{
public:
    Vector topLeft;

public:
    Vector bottomRight;

public:
    RectangleBorder(Vector &topLeft, Vector &bottomRight);

public:
    RectangleBorder(const Vector &topLeft, Vector &bottomRight);

public:
    RectangleBorder(Vector &topLeft, const Vector &bottomRight);

public:
    RectangleBorder(const Vector &topLeft, const Vector &bottomRight);

public:
    void drawRectangle(double r, double g, double b);
public:
    Vector getRectangleTopLeft();
public:
    Vector getRectangleBottomRight();
};

#endif