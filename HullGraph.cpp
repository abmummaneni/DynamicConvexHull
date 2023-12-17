
#include <climits>
#include <vector>
#include <algorithm>
#include <LEDA/graphics/window.h>
#include "VisTTree.h"
#include "ConcatenableQueue.h"
#include "Angle.h"
#include "Point.h"
#include "VisUtils.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <random>

int main() {
    VisTTree tree;
    VisUtils visUtils;
    leda::window W(800, 800);
    W.display(leda::window::center, leda::window::center);
    visUtils.setLedaWindow(&W);
    tree.setVisUtils(&visUtils);
    tree.setVisualize(false);
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> disX(50, 10);
    std::normal_distribution<> disY(50, 10);
    int powersOfTwo = 15;
    points.reserve(pow(2, powersOfTwo));
    for (int i = 0; i < pow(2, powersOfTwo); i++) {
        points.emplace_back(disX(gen), disY(gen));
    }
    for (int i = 0; i < pow(2, powersOfTwo); ++i) {
        tree.insert(points[i]);
    }
    tree.setVisualize(true);
    tree.drawHullGraph(tree.root);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;

}