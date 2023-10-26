/**
 * @file Point.h
 * @brief A point in 2D space.
 * @date 10/18/23
 * @author Abhinav Mummaneni
 */

#ifndef DYNAMICCONVEXHULL_POINT_H
#define DYNAMICCONVEXHULL_POINT_H


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
};


#endif //DYNAMICCONVEXHULL_POINT_H
