
#include "VisTTree.h"
#include "VisUtils.h"
#include <vector>
#include "ConcatenableQueue.h"
#include <chrono>
#include <thread>
#include <algorithm>
#include <iostream>
#include <queue>

#define DELAY 500

void VisTTree::descend(TTree::TNode *&n) {
    if (!visualize) {
        TTree::descend(n);
        return;
    }
    if (n->isLeaf or n->lower_hull->root == nullptr) {
        return;
    }
    std::vector<Point> lowerHull;
    ConcatenableQueue::getPoints(n->lower_hull->root, lowerHull);
    visUtils->drawHullGradient(lowerHull, false);

    std::vector<Point> upperHull;
    ConcatenableQueue::getPoints(n->upper_hull->root, upperHull);
    visUtils->drawHullGradient(upperHull, false);

    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    visUtils->deleteHull(lowerHull);
    visUtils->deleteHull(upperHull);

    std::vector<Point> leftHullLower;
    std::vector<Point> rightHullLower;
    ConcatenableQueue::getPoints(n->left->lower_hull->root, leftHullLower);
    ConcatenableQueue::getPoints(n->right->lower_hull->root, rightHullLower);


    std::vector<Point> leftHullUpper;
    std::vector<Point> rightHullUpper;
    ConcatenableQueue::getPoints(n->left->upper_hull->root, leftHullUpper);
    ConcatenableQueue::getPoints(n->right->upper_hull->root, rightHullUpper);
    std::reverse(leftHullUpper.begin(), leftHullUpper.end());
    std::reverse(rightHullUpper.begin(), rightHullUpper.end());
    leftHullLower.insert(leftHullLower.end(), leftHullUpper.begin(), leftHullUpper.end());
    rightHullUpper.insert(rightHullUpper.end(), rightHullLower.begin(), rightHullLower.end());
    visUtils->drawHull(leftHullLower);
    visUtils->drawHull(rightHullUpper);
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    visUtils->deleteHull(leftHullLower);
    visUtils->deleteHull(rightHullUpper);
    leftHullLower.clear();
    rightHullLower.clear();
    leftHullUpper.clear();
    rightHullUpper.clear();

    TTree::descend(n);

    ConcatenableQueue::getPoints(n->left->lower_hull->root, leftHullLower);
    ConcatenableQueue::getPoints(n->right->lower_hull->root, rightHullLower);
    ConcatenableQueue::getPoints(n->left->upper_hull->root, leftHullUpper);
    ConcatenableQueue::getPoints(n->right->upper_hull->root, rightHullUpper);
    std::reverse(leftHullUpper.begin(), leftHullUpper.end());
    std::reverse(rightHullUpper.begin(), rightHullUpper.end());
    leftHullLower.insert(leftHullLower.end(), leftHullUpper.begin(), leftHullUpper.end());
    rightHullUpper.insert(rightHullUpper.end(), rightHullLower.begin(), rightHullLower.end());
    visUtils->drawHullGradient(leftHullLower, true);
    visUtils->drawHullGradient(rightHullUpper, false);

    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    visUtils->deleteHull(leftHullLower);
    visUtils->deleteHull(rightHullUpper);
}

void VisTTree::setVisUtils(VisUtils *visUtils) {
    this->visUtils = visUtils;
}

void VisTTree::ascend(TTree::TNode *&n) {
    if (!visualize) {
        TTree::ascend(n);
        return;
    }
    if (n->isLeaf or n->lower_hull->root != nullptr) {
        return;
    }

    TTree::ascend(n);
    std::vector<Point> lowerhull;
    ConcatenableQueue::getPoints(n->lower_hull->root, lowerhull);
    visUtils->drawHullGradient(lowerhull, true);
    std::vector<Point> upperhull;
    ConcatenableQueue::getPoints(n->upper_hull->root, upperhull);
    visUtils->drawHullGradient(upperhull, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    visUtils->deleteHull(lowerhull);
    visUtils->deleteHull(upperhull);
}

bool VisTTree::insert(Point p) {
    if (!visualize) {
        return TTree::insert(p);
    }
    visUtils->resetGradientRatio();
    TNode *newLeaf = TTree::insert(p, root);
    visUtils->resetGradientRatio();
    ascend(root);
    return newLeaf != nullptr;
}

bool VisTTree::remove(Point p) {
    if (!visualize) {
        return TTree::remove(p);
    }
    visUtils->resetGradientRatio();
    bool found = TTree::remove(p, root);
    visUtils->resetGradientRatio();
    ascend(root);
    return found;
}

void VisTTree::setVisualize(bool _visualize) {
    visualize = _visualize;
}

void VisTTree::drawHullGraph(TTree::TNode *n) {
    //level order traversal of the tree
    std::queue<TTree::TNode *> q;
    q.push(n);
    int count = 0;
    int level = 0;
    while (not q.empty()){
        count++;
        //check if we are at a new level
        if (count == pow(2, level)){
            level++;
            count = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }
        TTree::TNode *curr = q.front();
        q.pop();
        if (curr->isLeaf or curr->lower_hull->root == nullptr) {
            continue;
        }
        std::vector<Point> lowerHull;
        ConcatenableQueue::getPoints(curr->lower_hull->root, lowerHull);
        visUtils->drawHullGradient(lowerHull, level);
        TTree::descend(curr);
        q.push(curr->left);
        q.push(curr->right);
    }
}


