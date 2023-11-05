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
using QNode = ConcatenableQueue::QNode;

void angleTest();
void CQueueTest();
void ttreTest();
void intersectionTest();

int main() {
    intersectionTest();
    return 0;
}
void angleTest() {
    // create a vector of angles representing the bottom of the unit circle
    // bottom of x^2 + y^2 = 1
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
    ConcatenableQueue q(Point(0, 0));
    ConcatenableQueue q2(Point(1, 1));
    ConcatenableQueue a(Point(0.5, 0.5));
    QNode *n = ConcatenableQueue::join(q.root, a.root, q2.root);
    ConcatenableQueue::inOrder(n);
    ConcatenableQueue::checkProperties(n, nullptr, nullptr);
    
    ConcatenableQueue q3(Point(2, 2));
    ConcatenableQueue q4(Point(3, 3));
    ConcatenableQueue a2(Point(2.5, 2.5));
    QNode *n2 = ConcatenableQueue::join(q3.root, a2.root, q4.root);
    ConcatenableQueue::inOrder(n2);
    ConcatenableQueue::checkProperties(n2, nullptr, nullptr);
    
    cout << "n3" << endl;
    ConcatenableQueue a3(Point(1.5, 1.5));
    QNode *n3 = ConcatenableQueue::join(n, a3.root, n2);
    ConcatenableQueue::inOrder(n3);
    ConcatenableQueue::checkProperties(n3, nullptr, nullptr);
    
   
    ConcatenableQueue q5(Point(4, 4));
    ConcatenableQueue q6(Point(5, 5));
    ConcatenableQueue a4(Point(4.5, 4.5));
    QNode *n4 = ConcatenableQueue::join(q5.root, a4.root, q6.root);
    ConcatenableQueue::inOrder(n4);
    ConcatenableQueue::checkProperties(n4, nullptr, nullptr);
    
    
    cout << "n5" << endl;
    ConcatenableQueue a5(Point(3.5, 3.5));
    QNode *n5 = ConcatenableQueue::join(n3, a5.root, n4);
    ConcatenableQueue::inOrder(n5);
    ConcatenableQueue::checkProperties(n5, nullptr, nullptr);
    
    ConcatenableQueue q7(Point(-2, -2));
    ConcatenableQueue q8(Point(-1, -1));
    ConcatenableQueue a6(Point(-1.5, -1.5));
    QNode *n6 = ConcatenableQueue::join(q7.root, a6.root, q8.root);
    ConcatenableQueue::inOrder(n6);
    ConcatenableQueue::checkProperties(n6, nullptr, nullptr);
    
    cout << "n7" << endl;
    ConcatenableQueue a7(Point(-0.5, -0.5));
    QNode *n7 = ConcatenableQueue::join(n6, a7.root, n5);
    ConcatenableQueue::inOrder(n7);
    ConcatenableQueue::checkProperties(n7, nullptr, nullptr);
    
    auto [left, right] = ConcatenableQueue::split(n7, [](Angle a) { return a > Angle(Point(1,1)); });
    cout << "left" << endl;
    ConcatenableQueue::inOrder(left);
    ConcatenableQueue::checkProperties(left, nullptr, nullptr);
    cout << "right" << endl;
    ConcatenableQueue::inOrder(right);
    ConcatenableQueue::checkProperties(right, nullptr, nullptr);
    
}

void intersectionTest(){
    Point l1 = Point(0, 0);
    Point l2 = Point(1, -1);
    Point r1 = Point(3, 3);
    Point r2 = Point(2, 0);
    
    double s = ((r1.x - l1.x) * (l2.y - l1.y) - (r1.y - l1.y) * (l2.x - l1.x)) /
               ((r2.y - r1.y) * (l2.x - l1.x) - (r2.x - r1.x) * (l2.y - l1.y));
    double x = r1.x + s * (r2.x - r1.x);
    cout << x << endl;
}