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
    static const enum Cases {Concave, Supporting, Reflex, Degenerate};

    
    // The cases describe how the angle is oriented relative to the line segment
    
    Point left, middle, right;
    double angle;

    Angle(Point left, Point middle, Point right);
    Angle(Point p);
    Angle() = default;
    
    bool isDegenerate();
    
    Cases getCase(Point &p);
    
    
    static bool isCCW(Point &first, Point &second, Point &third);
    
    static bool isCW(Point &first, Point &second, Point &third);
    
    static std::pair<Cases, Cases> getCases(Angle leftAngle, Angle rightAngle);

    friend std::ostream &operator<<(std::ostream &os, const Angle &angle);

    bool operator<(const Angle &rhs) const;

    bool operator>(const Angle &rhs) const;

    bool operator<=(const Angle &rhs) const;

    bool operator>=(const Angle &rhs) const;
};


#endif //DYNAMICCONVEXHULL_ANGLE_H
