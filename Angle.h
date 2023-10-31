//
// Created by Abhinav Mummaneni on 10/29/23.
//

#ifndef DYNAMICCONVEXHULL_ANGLE_H
#define DYNAMICCONVEXHULL_ANGLE_H

#include "Point.h"

class Angle {
    static const enum Side {Left, Right};
    static const enum Cases {Concave, Supporting, Reflex};
public:
    
    // The cases describe how the angle is oriented relative to the line segment
    
    Point left, middle, right;
    double angle;

    Angle(Point left, Point middle, Point right);
    
    Cases getCase(Point *p, Side side);
    double getAngle(Point &a, Point &b, Point &c);
};


#endif //DYNAMICCONVEXHULL_ANGLE_H
