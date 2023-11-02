#include <iostream>
#include "TTree.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
#include <cmath>
#include "Angle.h"
using namespace std;
void angleTest();
int main() {
    angleTest();
    return 0;
}
void angleTest(){
    Angle a = Angle(Point(0, 1), Point(0, 1), Point(1,0));
    cout << a.angle << endl;
    Point *p = new Point(1, 1);
    cout << a.getCase(p, Angle::Left);
    delete p;
}
void ttreTest(){
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
    for (Point p : points) {
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
    for (Point p : points) {
        cout << "removing " << p.x << endl;
        t.remove(p);
        t.displayTree();
        t.checkProperties();
    }
}