#include <iostream>
#include "TTree.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
#include <cmath>
#include "Angle.h"
#include "ConcatenableQueue.h"

using namespace std;

void angleTest();

int main() {
    angleTest();
    return 0;
}

void angleTest() {
    // create a vector of angles representing the bottom of the unit circle
    // x^2 + y^2 = 1
    vector<Point> points;
    for (int i = -10; i < 10; ++i) {
        double x = (double) i / 10;
        double y = -sqrt(1 - (x * x));
        points.emplace_back(x, y);
    }
    // For every triple of points create an angle
    vector<Angle> angles;
    angles.emplace_back(points[0], points[0], points[1]);
    for (int i = 1; i < points.size() - 3; ++i) {
        angles.emplace_back(points[i], points[i + 1], points[i + 2]);
    }
    angles.emplace_back(points[points.size() - 2], points[points.size() - 1], points[points.size() - 1]);
    cout << angles.size() << "angles created" << endl;
    Point test = Point(2, -0.5);
    for (Angle a: angles) {
        cout << "angle: " << a << endl;
        cout << "case: " << a.getCase(&test, Angle::Left) << endl;
    }
}

void ttreTest() {
    TTree t;
    cout << "created" << endl;
    vector<Point> points;
    for (int i = 0; i < 40; ++i) {
        Point randPoint = Point(random() % 100, random() % 100);
        points.push_back(randPoint);
        cout << "inserting " << i << " " << randPoint.x << endl;
        t.insert(randPoint);
        t.displayTree();
        cout << "checking properties" << endl;
        t.checkProperties();
    }
    std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));
    for (Point p: points) {
        cout << "removing " << p.x << endl;
        t.remove(p);
        t.displayTree();
        t.checkProperties();
    }
    points.clear();
    for (int i = 0; i < 40; ++i) {
        Point randPoint = Point(random() % 100, random() % 100);
        points.push_back(randPoint);
        cout << "inserting " << i << " " << randPoint.x << endl;
        t.insert(randPoint);
        t.displayTree();
        cout << "checking properties" << endl;
        t.checkProperties();
    }
    std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));
    for (Point p: points) {
        cout << "removing " << p.x << endl;
        t.remove(p);
        t.displayTree();
        t.checkProperties();
    }
}

void CQueueTest() {
    
}