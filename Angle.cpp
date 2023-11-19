//
// Created by Abhinav Mummaneni on 10/29/23.
//

#include "Angle.h"
#include <cmath>
#include <iostream>
#include <cassert>

/**
 * @brief Determines which of the 3 cases the angle is in with respect to a line segment from p to middle
 * @param p The point which will form a segment with middle 
 * @return The case of the point relative to the angle
 */
Angle::Cases Angle::getCase(Point &p) {
    // Let the points of the angle be A, B, and C from left to right
    // Is the angle just a point (Both A and C are placeholder infinity)
    if (left.y == INFINITY and right.y == INFINITY){
        return Supporting;
    }
    
    // Is p on the right side of the plane BA (closed if A exists, open if A is placeholder infinity)
    bool isRightOfBA = (left.y == INFINITY) ? p.x > middle.x : not isCCW(middle, left, p);
    // Is p on the left side of the plane BC (closed if C exists, open if C is placeholder infinity)
    bool isLeftOfBC = (right.y == INFINITY) ? p.x < middle.x : not isCW(middle, right, p); 
    
    if (isRightOfBA and isLeftOfBC) {
        // If p is on the right side of BA and the left side of BC, then it is in the angle ABC
        return Concave;
    }
    
    // Reflex Case, p is in the angle opposite of ABC, this is the intersection of 2 half planes
    if (not isRightOfBA and not isLeftOfBC) {
        return Reflex;
    }
    // Otherwise must be supporting
    return Supporting;
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
}

std::ostream &operator<<(std::ostream &os, const Angle &angle) {
    os << "left: " << angle.left << " middle: " << angle.middle << " right: " << angle.right;
    return os;
}

Angle::Angle(Point p) {
    left = middle = right = p;
    left.y = right.y = INFINITY;
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

std::pair<Angle::Cases, Angle::Cases> Angle::getCases(Angle leftAngle, Angle rightAngle) {
    return {leftAngle.getCase(rightAngle.middle),
            rightAngle.getCase(leftAngle.middle)};
}

bool Angle::isCCW(Point &first, Point &second, Point &third) {
    /* HW1!
     * Calculate determinant of:
     * | first.x  first.y  1 |
     * | second.x second.y 1 |
     * | third.x  third.y  1 |
     * If the determinant is positive, then the points are in CCW order and thus form a left turn
     */
    return first.x * second.y + first.y * third.x + second.x * third.y - third.x * second.y - third.y * first.x -
           second.x * first.y > 0;
}

bool Angle::isDegenerate() {
    return left.x == right.x;
}

bool Angle::isCW(Point &first, Point &second, Point &third) {
    return first.x * second.y + first.y * third.x + second.x * third.y - third.x * second.y - third.y * first.x -
           second.x * first.y < 0;
}

