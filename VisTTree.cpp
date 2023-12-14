
#include "VisTTree.h"
#include "VisUtils.h"
#include <vector>
#include "ConcatenableQueue.h"
#include <chrono>
#include <thread>
void VisTTree::descend(TTree::TNode *&n) {
    if (n->isLeaf or n->lower_hull->root == nullptr) {
        return;
    }
    std::vector<Point> hull;
    ConcatenableQueue::getPoints(n->lower_hull->root, hull);
    visUtils->drawHullGradient(hull, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    visUtils->deleteHull(hull);
    hull.clear();
    
    TTree::descend(n);
    
    std::vector<Point> leftHull;
    std::vector<Point> rightHull; 
    ConcatenableQueue::getPoints(n->left->lower_hull->root, leftHull);
    ConcatenableQueue::getPoints(n->right->lower_hull->root, rightHull);
    visUtils->drawHullGradient(leftHull, true);
    visUtils->drawHullGradient(rightHull, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    visUtils->deleteHull(leftHull);
    visUtils->deleteHull(rightHull);
}

void VisTTree::setVisUtils(VisUtils *visUtils) {
    this->visUtils = visUtils;
}
void VisTTree::ascend(TTree::TNode *&n) {
    if (n->isLeaf or n->lower_hull->root != nullptr) {
        return;
    }
    
    TTree::ascend(n);
    std::vector<Point> hull;
    ConcatenableQueue::getPoints(n->lower_hull->root, hull);
    visUtils->drawHullGradient(hull, true);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    visUtils->deleteHull(hull);
}

bool VisTTree::insert(Point p) {
    visUtils->resetGradientRatio();
    TNode *newLeaf = TTree::insert(p, root);
    visUtils->resetGradientRatio();
    ascend(root);
    return newLeaf != nullptr;
}
bool VisTTree::remove(Point p) {
    visUtils->resetGradientRatio();
    bool found = TTree::remove(p, root);
    visUtils->resetGradientRatio();
    ascend(root);
    return found;
}