//
// Created by Abhinav Mummaneni on 10/29/23.
//

#ifndef DYNAMICCONVEXHULL_ANGLE_H
#define DYNAMICCONVEXHULL_ANGLE_H

#include <ostream>
#include "Point.h"

class Angle {
public:
    static const enum Side {Left, Right};
    static const enum Cases {Concave, Supporting, Reflex};

    
    // The cases describe how the angle is oriented relative to the line segment
    
    Point left, middle, right;
    double angle;

    Angle(Point left, Point middle, Point right);
    Angle(Point p);
    Angle() = default;
    
    Cases getCase(Point *p, Side side);
    double getAngle(Point &a, Point &b, Point &c);

    friend std::ostream &operator<<(std::ostream &os, const Angle &angle);
};


#endif //DYNAMICCONVEXHULL_ANGLE_H
