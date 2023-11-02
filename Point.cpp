//
// Created by Abhinav Mummaneni on 10/18/23.
//

#include "Point.h"

bool Point::operator<(const Point &rhs) const {
    return x < rhs.x or (x == rhs.x and y < rhs.y);
}

bool Point::operator>(const Point &rhs) const {
    return rhs < *this;
}

bool Point::operator<=(const Point &rhs) const {
    return not (rhs < *this);
}

bool Point::operator>=(const Point &rhs) const {
    return not (*this < rhs);
}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x and y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return not (rhs == *this);
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}
