#include <iostream>
#include "TTree.h"
#include <random>
using namespace std;
int main() {
    TTree t;
    cout << "created" << endl;
    for (int i = 0; i < 40; ++i) {
        Point randPoint = Point(random() % 100, random() % 100);
        cout << "inserting " << i << " " << randPoint.x << endl;
        t.insert(randPoint);
        t.displayTree();
    }
    return 0;
}
