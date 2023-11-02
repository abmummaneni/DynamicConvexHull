/**
 * @file Point.h
 * @brief A point in 2D space.
 * @date 10/18/23
 * @author Abhinav Mummaneni
 */

#ifndef DYNAMICCONVEXHULL_POINT_H
#define DYNAMICCONVEXHULL_POINT_H


#include <ostream>

class Point {
public:
    double x;
    double y;

    Point() = default;

    Point(double x, double y);

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    bool operator<(const Point &rhs) const;

    bool operator>(const Point &rhs) const;

    bool operator<=(const Point &rhs) const;

    bool operator>=(const Point &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};


#endif //DYNAMICCONVEXHULL_POINT_H
