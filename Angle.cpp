//
// Created by Abhinav Mummaneni on 10/29/23.
//

#include "Angle.h"
#include <cmath>
/**
 * @brief Determines which of the 3 cases the angle is in with respect to a line segment from p to middle
 * @param p The point which will form a segment with middle 
 * @return 
 */
Angle::Cases Angle::getCase(Point *p, Side side) {
    double bridgeAngle = getAngle(side == Left ? right : left, middle, *p); // side is the side that the point is on
    if (bridgeAngle < angle) return Reflex;
    else if (bridgeAngle > M_PI) return Concave;
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

Angle::Angle(Point left, Point middle, Point right) {
    this->left = left;
    this->middle = middle;
    this->right = right;
    this->angle = getAngle(left, middle, right);
}
