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
};

class CircleBorder : public Border
{
public:
    double r;
public:
    Vector location;

public:
    CircleBorder(const Vector &location, double r);
public:
    CircleBorder(Vector &location, double r);
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
};

#endif