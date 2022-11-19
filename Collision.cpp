#include <stdlib.h>
#include <cmath>
#include <glut.h>
#include <list>
#include <functional>
#include "Border.h"
#include "BaseTypes.h"
#include "DrawTools.h"
#include <string>

class CollisionCase
{
public:
    std::list<Border *> borders;

    std::function<void(Vector &boundDirections, double pointX, double pointY)> callback;

public:
    CollisionCase(std::list<Border *> borders, std::function<void(Vector &boundDirections, double pointX, double pointY)> callback)
    {
        this->borders = borders;
        this->callback = callback;
    };

public:
    void runCallback(Vector &boundDirections, double pointX, double pointY)
    {
        callback(boundDirections, pointX, pointY);
    }
};

class Collision
{

private:
    bool collided;
public:
    Vector direction;

public:
    Vector collisionPoint;

public:
    Collision(bool collided, Vector &direction, Vector &collisionPoint) : direction(direction.x, direction.y), collisionPoint(collisionPoint.x, collisionPoint.y) {
        this->collided = collided;
    }

    explicit operator bool() const
    {
        return collided;
    }
};

class CollisionDetector
{
    std::list<CollisionCase> collisionCases;

public:
    CollisionDetector(std::list<CollisionCase> collisionCases)
    {
        this->collisionCases = collisionCases;
    }

public:
    void detectCollisions()
    {
        std::list<CollisionCase>::iterator cCase;
        for (cCase = collisionCases.begin(); cCase != collisionCases.end(); ++cCase)
        {
            for (Border *border1 : cCase->borders)
            {
                for (std::list<Border *>::iterator it = --cCase->borders.end(); border1 != *it; it--)
                {
                    Border *border2 = *it;
                    if (border1->shape == BorderShape::circle && border2->shape == BorderShape::rectangle)
                    {
                        int r = border1->getCircleRadius();
                        Collision myCollision = circleRectCollisionDetect(*(CircleBorder *)(border1), *(RectangleBorder *)(border2));
                        if (myCollision)
                        {
                            cCase->callback(myCollision.direction, myCollision.collisionPoint.x, myCollision.collisionPoint.y);
                        }
                    }
                    else if (border2->shape == BorderShape::circle && border1->shape == BorderShape::rectangle)
                    {
                        Collision myCollision = circleRectCollisionDetect(*(CircleBorder *)(border2), *(RectangleBorder *)border1);
                        if (myCollision)
                        {
                            cCase->callback(myCollision.direction, myCollision.collisionPoint.x, myCollision.collisionPoint.y);
                        }
                    }
                    else if (border1->shape == BorderShape::circle && border2->shape == BorderShape::circle)
                    {
                        Collision myCollision = circleCircleCollisionDetect(*(CircleBorder *)border1, *(CircleBorder *)border2);
                        if (myCollision) {
                            cCase->callback(myCollision.direction, myCollision.collisionPoint.x, myCollision.collisionPoint.y); //TODO: ACTUAL STUFF
                        }
                    }
                }
            }
        }
    }

private:
    Collision circleRectCollisionDetect(CircleBorder &circle, RectangleBorder &rect)
    {
        Vector cSpeed = *circle.velocity;
        double leftDistance = rect.topLeft.x - (*circle.location).x;
        double rightDistance = rect.bottomRight.x - (*circle.location).x;
        double topDistance = rect.topLeft.y - (*circle.location).y;
        double bottomDistance = rect.bottomRight.y - (*circle.location).y;

        bool exceededLeft = leftDistance < circle.r + cSpeed.x;
        bool exceededRight = rightDistance > -circle.r + cSpeed.x;
        bool exceededTop = topDistance > -circle.r + cSpeed.y;
        bool exceededBottom = bottomDistance < circle.r + cSpeed.y;
        bool collided = exceededLeft && exceededRight && exceededTop && exceededBottom;

        double closestX = 0;
        double closestY = 0;
        int xDir;
        int yDir;

        if (abs(leftDistance) < abs(rightDistance))
        {
            closestX = leftDistance;
            xDir = -1;
        }
        else
        {
            closestX = rightDistance;
            xDir = 1;
        }

        if (abs(topDistance) < abs(bottomDistance))
        {
            closestY = topDistance;
            yDir = 1;
        }
        else
        {
            closestY = bottomDistance;
            yDir = -1;
        }

        Vector collisionPoint((*circle.location).x, (*circle.location).y);

        if (!collided)
        {
            yDir = 0;
            xDir = 0;
        }
        else if (abs(closestX) < abs(closestY))
        {
            collisionPoint.x += closestX;
            yDir = 0;
        }
        else
        {
            collisionPoint.y += closestY;
            xDir = 0;
        }

        Vector directionVector(xDir, yDir);
        if (collided)
        {
            drawPointLocation(collisionPoint.x + circle.r * directionVector.x, collisionPoint.y + circle.r * directionVector.y);
        }

        return Collision(collided, directionVector, collisionPoint);
    }

private:
    Collision circleCircleCollisionDetect(CircleBorder &circle1, CircleBorder &circle2)
    {
        double xDisplacement = circle1.location->x + circle1.velocity->x - circle2.location->x - circle2.velocity->x;
        double yDisplacement = circle1.location->y + circle1.velocity->x - circle2.location->y - circle2.velocity->y;

        // Get distance by sqrt(x^2 + y^2)
        double distance = sqrt(pow(abs(xDisplacement), 2) + pow(abs(yDisplacement), 2));

        Vector unitDirectionVector = Vector(xDisplacement/distance, yDisplacement/distance);

        bool collided = distance - (circle1.r + circle2.r) < 0;
        Vector reboundLocation = Vector(circle2.location->x + circle2.velocity->x + (unitDirectionVector.x * circle2.r), circle2.location->y + circle2.velocity->y + (unitDirectionVector.y * circle2.r));
        if (collided) {
            drawPointLocation(reboundLocation.x, reboundLocation.y);
        }

        return Collision(collided, *circle2.velocity, reboundLocation);

    }
};
