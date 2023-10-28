#include <iostream>
#include "TTree.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
using namespace std;
int main() {
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
        assert(t.remove(p));
        t.displayTree();
        t.checkProperties();
    }
    return 0;
}
