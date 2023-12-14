//
// Created by Abhinav Mummaneni on 10/29/23.
//

#ifndef DYNAMICCONVEXHULL_ANGLE_H
#define DYNAMICCONVEXHULL_ANGLE_H

#include <ostream>
#include "Point.h"

class Angle {
public:
    
    enum Cases {Concave, Supporting, Reflex};

    // The cases describe how the angle is oriented relative to the line segment
    
    Point left, middle, right;

    Angle(Point left, Point middle, Point right);
    Angle() = default;
    
    Cases getLowerCase(Point &p);
    Cases getUpperCase(Point &p);
    
    
    static bool isCCW(Point &first, Point &second, Point &third);
    
    static bool isCW(Point &first, Point &second, Point &third);
    
    static std::pair<Cases, Cases> getCases(Angle leftAngle, Angle rightAngle, bool hullType);

    friend std::ostream &operator<<(std::ostream &os, const Angle &angle);

    bool operator<(const Angle &rhs) const;

    bool operator>(const Angle &rhs) const;

    bool operator<=(const Angle &rhs) const;

    bool operator>=(const Angle &rhs) const;
};


#endif //DYNAMICCONVEXHULL_ANGLE_H
