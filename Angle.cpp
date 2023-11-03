//
// Created by Abhinav Mummaneni on 10/29/23.
//

#include "Angle.h"
#include <cmath>
#include <iostream>

/**
 * @brief Determines which of the 3 cases the angle is in with respect to a line segment from p to middle
 * @param p The point which will form a segment with middle 
 * @param side The side which the angle is relative to the point 
 * @return 
 */
Angle::Cases Angle::getCase(Point *p, Side side) {
    if (angle == 0) return Supporting; // 2 points are always supporting
    Angle bridge = Angle(side == Left ? left : right, middle, *p);
    double bridgeAngle = bridge.angle;
    if (bridgeAngle < angle) return Concave;
    else if (bridgeAngle > M_PI) return Reflex;
    else return Supporting;
}

/**
 * @brief Calculates the counterclockwise angle between bc and ba
 * @param a The first point
 * @param b The second point
 * @param c The third point
 * @return The angle between the 3 points
 */
double Angle::getAngle(Point &a, Point &b, Point &c) {
    double ba = std::atan2(b.y - a.y, b.x - a.x);
    double bc = std::atan2(b.y - c.y, b.x - c.x);
    double angle = ba - bc;
    if (angle < 0) angle += 2 * M_PI;
    return angle;
}

/**
 * @brief Constructs an angle from 3 points
 * @param left
 * @param middle 
 * @param right
 * @details If all three points are the same, treat the angle as 0. If two points are the same, 
 * (left and middle or middle and right), then create the angle by forming a vertical line at the middle point and
 * then use the other unique point to form the angle. Make sure this angle is non reflex.
 * Otherwise, calculate the angle normally.
 */
Angle::Angle(Point left, Point middle, Point right) {
    this->left = left;
    this->middle = middle;
    this->right = right;
    if (left == middle and right == middle) angle = 0;
    else if (left == middle) {
        Point temp = Point(middle.x, middle.y + 1);
        angle = getAngle(right, middle, temp);
        if (angle > M_PI) angle = 2 * M_PI - angle;
    } else if (right == middle) {
        Point temp = Point(middle.x, middle.y + 1);
        angle = getAngle(left, middle, temp);
        if (angle > M_PI) angle = 2 * M_PI - angle;
    } else angle = getAngle(left, middle, right);
}

std::ostream &operator<<(std::ostream &os, const Angle &angle) {
    os << "left: " << angle.left << " middle: " << angle.middle << " right: " << angle.right << " angle: "
       << angle.angle;
    return os;
}

Angle::Angle(Point p) {
    left = p;
    middle = p;
    right = p;
    angle = 0;
}

bool Angle::operator<(const Angle &rhs) const {
    return middle < rhs.middle;
}

bool Angle::operator>(const Angle &rhs) const {
    return rhs < *this;
}

bool Angle::operator<=(const Angle &rhs) const {
    return !(rhs < *this);
}

bool Angle::operator>=(const Angle &rhs) const {
    return !(*this < rhs);
}
