/**
 * @file ConcatenableQueue.cpp
 * @date 10/18/23
 * @author Abhinav Mummaneni
 * @details Concatenable Queue is implemented as an AVL tree that uses the splitHull and join2 functions.
 */

#include "ConcatenableQueue.h"
#include <cassert>

ConcatenableQueue::ConcatenableQueue() = default;

ConcatenableQueue::~ConcatenableQueue() = default;

void ConcatenableQueue::concatenate(ConcatenableQueue *left, ConcatenableQueue *right) {

}

void ConcatenableQueue::splitHull(ConcatenableQueue *&left, ConcatenableQueue *&right) {

}

ConcatenableQueue::ConcatenableQueue(Point p) {
    root = new QNode(Angle(p));
}

ConcatenableQueue::QNode *ConcatenableQueue::join2(QNode *&T1, QNode *&T1Max, QNode *&T2Min, QNode *&T2) {
}

/**
 * @brief Joins two trees together and uses the bridge to connect them. All values in T1 are less than k 
 * which is less than all values in T2.
 * @param T1 The "left" tree to be joined.
 * @param k A middle value, in practice will be either the previous max of T1 or the previous min of T2 which has just 
 * been removed so that this function can run @see join2
 * @param T2 The "right" tree to be joined.
 * @return A pointer to the new merged tree.
 */
ConcatenableQueue::QNode *ConcatenableQueue::join(ConcatenableQueue::QNode *&T1, ConcatenableQueue::QNode *&k,
                                                  ConcatenableQueue::QNode *&T2) {
    int t1Height = getHeight(T1);
    int t2Height = getHeight(T2);

}

/**
 * @brief Helper function for join. Called when the height of T1 is greater than the getHeight of T2.
 * @param T1 Left tree to be joined.
 * @param k Middle value
 * @param T2 Right tree to be joined.
 * @return A pointer to the new merged tree.
 * @details This function recursively traces down the right spine of T1 until a suitable getHeight node, c, is found.
 * It then uses the middle node k to join the two trees by creating a new node with value k, left child c, and right
 * child T2. Rotations and getHeight updates are performed as necessary to maintain the AVL property.
 * 
 */
ConcatenableQueue::QNode *ConcatenableQueue::joinRight(QNode *&T1, Angle k,
                                                       QNode *&T2) {
    QNode *l = T1->left;
    Angle _k = T1->angle;
    QNode *c = T1->right;
    if (c->height <= T2->height + 1) { // T2->height <= c->height because we stop ASAP
        QNode *connection = new QNode(c, k, T2);
        if (getHeight(connection) <= getHeight(l) + 1) { // If T1 is still balanced
            delete T1;
            return new QNode(l, _k, connection);
        } else { // T1 is right heavy. Since T2->height <= c->height we RL rotate
            delete T1;
            return rotateLeft(new QNode(l, _k, rotateRight(connection)));
        }
    }
    QNode *connection = joinRight(c, k, T2);
    if (getHeight(connection) <= getHeight(l) + 1) { // If T1 is still balanced
        delete T1;
        return new QNode(l, _k, connection);
    } else { // T1 is right heavy, but we know this is an RR case since now at an ancestor
        delete T1;
        return rotateLeft(new QNode(l, _k, connection));
    }
}

int ConcatenableQueue::getHeight(ConcatenableQueue::QNode *&n) {
    return n == nullptr ? -1 : n->height;
}

ConcatenableQueue::QNode *ConcatenableQueue::rotateLeft(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return nullptr;
    QNode *r = n->right;
    n->right = r->left;
    r->left = n;
    n->height = std::max(getHeight(n->left), getHeight(n->right)) + 1;
    r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
    return r;
}

ConcatenableQueue::QNode *ConcatenableQueue::rotateRight(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return nullptr;
    QNode *l = n->left;
    n->left = l->right;
    l->right = n;
    n->height = std::max(getHeight(n->left), getHeight(n->right)) + 1;
    l->height = std::max(getHeight(l->left), getHeight(l->right)) + 1;
    return l;
}


/**
 * @brief Checks that the tree maintains all AVL and BST properties.
 * @param n 
 * @return 
 */
void ConcatenableQueue::checkProperties(ConcatenableQueue::QNode *n, ConcatenableQueue::QNode *min,
                                        ConcatenableQueue::QNode *max) {
    if (n == nullptr) return;
    if (min != nullptr) assert(n->angle > min->angle);
    if (max != nullptr) assert(n->angle < max->angle);

    assert(n->height == std::max(getHeight(n->left), getHeight(n->right)) + 1);
    assert(n->height == checkHeight(n));
    assert(std::abs(getHeight(n->left) - getHeight(n->right)) <= 1);
    checkProperties(n->left, min, n);
    checkProperties(n->right, n, max);

}

int ConcatenableQueue::checkHeight(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return -1;
    return std::max(checkHeight(n->left), checkHeight(n->right)) + 1;
}

void ConcatenableQueue::findBridge(ConcatenableQueue *left, ConcatenableQueue *right) {
    QNode *l = left->root;
    QNode *r = right->root;
    Angle::Cases lCase = l->angle.getCase(&r->angle.middle, Angle::Left);
    Angle::Cases rCase = r->angle.getCase(&l->angle.middle, Angle::Right);
    if (lCase == Angle::Supporting and rCase == Angle::Supporting) { // Terminating Case

    } else if (lCase == Angle::Supporting) {
        r = (rCase == Angle::Concave) ? r->left : r->right;
    } else if (rCase == Angle::Supporting) {
        l = (lCase == Angle::Concave) ? l->right : l->left;
    } else if (lCase == Angle::Reflex and rCase == Angle::Reflex) {
        l = l->left;
        r = r->right;
    } else if (lCase == Angle::Concave and rCase == Angle::Reflex) {
        r = r->right;
    } else if (lCase == Angle::Reflex and rCase == Angle::Concave) {
        l = l->left;
    } else if (lCase == Angle::Concave and rCase == Angle::Concave) { // Complex case!
        
    }


}

ConcatenableQueue::QNode::QNode(ConcatenableQueue::QNode *l, Angle a, ConcatenableQueue::QNode *r) {
    left = l;
    right = r;
    angle = a;
    height = std::max(getHeight(l), getHeight(r)) + 1;
}


ConcatenableQueue::QNode::QNode(Angle a) {
    angle = a;
    height = 0;
    left = nullptr;
    right = nullptr;
}
