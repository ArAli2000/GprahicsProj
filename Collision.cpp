#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include <list>
#include <functional>
#include "Border.h"

class CollisionCase
{
    std::list<Border> borders;
    std::function<void(void)> callback;

public:
    CollisionCase(std::list<Border> borders, std::function<void(void)> callback)
    {   
        this->borders = borders;
        this->callback = callback;
    };

    void runCallback()
    {
        callback();
    }
};

class CollisionDetector
{
    std::list<CollisionCase> collisionCases;

public:
    bool circleRectCollisionDetect(CircleBorder circle, RectangleBorder rect) {
        bool exceededLeft = rect.topLeft.x - circle.location.x - circle.r <= 0;
        bool exceededRight = circle.location.x - circle.r - rect.bottomRight.x <= 0;
        bool exceededTop = rect.topLeft.y - circle.location.y - circle.r <= 0;
        bool exceededBottom = circle.location.y - circle.r - rect.bottomRight.y <= 0;

        return exceededLeft && exceededRight && exceededTop && exceededBottom;
    }

public:
    bool circleCircleCollisionDetect(CircleBorder circle1, CircleBorder circle2) {
        double xDistance = abs(circle1.location.x - circle2.location.x);
        double yDistance = abs(circle1.location.y - circle2.location.y);

        //Get distance by sqrt(x^2 + y^2)
        double distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));

        //If the distance between them is less than the sum of the radii, then they have collided
        return distance - (circle1.r + circle2.r) <= 0;
    }

};
