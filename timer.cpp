#include "TTree.h"
#include "Point.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include "timer.h"
int main() {
    timer t;
    t.addTest();
    return 0;
}

void timer::addTest() {
    TTree tree;
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1000, 1000);
    int powersOfTwo = 18;
    points.reserve(pow(2, powersOfTwo));
    for (int i = 0; i < pow(2, powersOfTwo); i++) {
        points.emplace_back(dis(gen), dis(gen));
    }
    for (int i = 0; i < powersOfTwo; ++i) {
        for (int j = 0; j < pow(2, i) - 1; ++j) {
            tree.insert(points[pow(2, i) + j]);
        }
        auto start = std::clock();
        tree.insert(points[pow(2, i) - 1]);
        auto end = std::clock();
        auto duration = end - start;
        // Print (log(n)^2, time) in microseconds. 
        // This ends up looking linear as expected by the O(log(n)^2) runtime of the algorithm.
        std::cout << "(" << pow(i, 2)  << "," << 1000000 * duration / CLOCKS_PER_SEC << ")" << std::endl;
    }
}
