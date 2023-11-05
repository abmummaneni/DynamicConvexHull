/**
 * @file ConcatenableQueue.cpp
 * @date 10/18/23
 * @author Abhinav Mummaneni
 * @details Concatenable Queue is implemented as an AVL tree that uses the splitHull and join2 functions.
 */

#include "ConcatenableQueue.h"
#include <cassert>
#include <iostream>


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
    if (T1 == nullptr) return T2;
    if (T2 == nullptr) return T1;
    int t1Height = getHeight(T1);
    int t2Height = getHeight(T2);

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
ConcatenableQueue::QNode *ConcatenableQueue::join(QNode *T1, QNode *k, QNode *T2) {
    int t1Height = getHeight(T1);
    int t2Height = getHeight(T2);
    if (t1Height == t2Height) {
        k->left = T1;
        k->right = T2;
        updateHeight(k);
        return k;
    }
    if (t1Height > t2Height) {
        return joinRight(T1, k, T2);
    } else {
        return joinLeft(T1, k, T2);
    }

}

/**
 * @brief Helper function for join. Called when the height of T1 is greater than the getHeight of T2.
 * @param T1 Left tree to be joined.
 * @param k Middle key 
 * @param T2 Right tree to be joined.
 * @return A pointer to the new merged tree.
 * @details This function recursively traces down the right spine of T1 until a suitable getHeight node, c, is found.
 * It then uses the middle key k to join the two trees by creating a new node with value k, left child c, and right
 * child T2. Rotations and getHeight updates are performed as necessary to maintain the AVL property.
 * 
 */
ConcatenableQueue::QNode *ConcatenableQueue::joinRight(QNode *T1, QNode *k,
                                                       QNode *T2) {
    if (T1 == nullptr) {
        // Edge case that only occurs when T2 is a null pointer
        // And the minimum height node on the right spine of original T1 is one (i.e has a left child but no right child) 
        // Thus we have gone to the null pointer right child and should now return a node with value k
        k->left = k->right = nullptr;
        return k;
    }
    QNode *l = T1->left;
    QNode *c = T1->right;
    if (getHeight(c) <= getHeight(T2) + 1) { // T2->height <= c->height because we stop ASAP
        k->left = c;
        k->right = T2;
        updateHeight(k);
        if (getHeight(k) <= getHeight(l) + 1) { // If T1 is still balanced
            T1->right = k;
            updateHeight(T1);
            return T1;
        } else { // T1 is right heavy. Since T2->height <= c->height we RL rotate
            T1->right = rotateRight(k);
            updateHeight(T1);
            return rotateLeft(T1);
        }
    }
    T1->right = joinRight(c, k, T2);
    if (getHeight(T1->right) <= getHeight(l) + 1) { // If T1 is still balanced
        updateHeight(T1);
        return T1;
    } else { // T1 is right heavy, but we know this is an RR case since now at an ancestor
        updateHeight(T1);
        return rotateLeft(T1);
    }
}

ConcatenableQueue::QNode *
ConcatenableQueue::joinLeft(QNode *T1, QNode *k, QNode *T2) {
    if (T2 == nullptr) { // Edge case that only occurs when T1 is a null pointer
        // And the maximum height node on the left spine of original T2 is one (i.e has a right child but no left child) 
        // Thus we have gone to the null pointer left child and should now return a node with value k
        k->left = k->right = nullptr;
        return k;
    }
    QNode *c = T2->left;
    QNode *r = T2->right;
    if (getHeight(c) <= getHeight(T1) + 1) { // T1->height <= c->height because we stop ASAP
        k->left = T1;
        k->right = c;
        updateHeight(k);
        if (getHeight(k) <= getHeight(r) + 1) { // If T2 is still balanced
            T2->left = k;
            updateHeight(T2);
            return T2;
        } else { // T2 is left heavy. Since T1->height <= c->height we LR rotate
            T2->left = rotateLeft(k);
            updateHeight(T2);
            return rotateRight(T2);
        }
    }
    T2->left = joinLeft(T1, k, c);
    if (getHeight(T2->left) <= getHeight(r) + 1) { // If T2 is still balanced
        updateHeight(T2);
        return T2;
    } else { // T2 is left heavy, but we know this is an LL case since now at an ancestor
        updateHeight(T2);
        return rotateRight(T2);
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

using
enum Angle::Cases;

std::pair<ConcatenableQueue::QNode *, ConcatenableQueue::QNode *>
ConcatenableQueue::findBridge(ConcatenableQueue *left, ConcatenableQueue *right) {
    QNode *l = left->root;
    QNode *r = right->root;
    double minX = getMin(l)->middle.x;
    double maxX = getMax(r)->middle.x;
    double midLine = 0.5 * (minX + maxX);
    for (auto [lCase, rCase] = Angle::getCases(l->angle, r->angle);
         not(lCase == Supporting and rCase == Supporting);
         std::tie(lCase, rCase) = Angle::getCases(l->angle, r->angle)) {

        if (lCase == Supporting) {
            r = (rCase == Concave) ? r->left : r->right;
        } else if (rCase == Supporting) {
            l = (lCase == Concave) ? l->right : l->left;
        } else if (lCase == Reflex and rCase == Reflex) {
            l = l->left;
            r = r->right;
        } else if (lCase == Concave and rCase == Reflex) {
            r = r->right;
        } else if (lCase == Reflex and rCase == Concave) {
            l = l->left;
        } else if (lCase == Concave and rCase == Concave) { // Complex case!
            Point l1 = l->angle.middle;
            Point l2 = l->angle.right;

            Point r1 = r->angle.middle;
            Point r2 = r->angle.left;

            //Must find intersection of lines l1 l2 and r1 r2
            // Create parametric equations 

            // l1 + t(l2 - l1) = r1 + s(r2 - r1)
            // l1.x + t(l2.x - l1.x) = r1.x + s(r2.x - r1.x)
            // l1.y + t(l2.y - l1.y) = r1.y + s(r2.y - r1.y)
            // Create system with unknowns t and s
            // t(l2.x - l1.x) - s(r2.x - r1.x) = r1.x - l1.x
            // t(l2.y - l1.y) - s(r2.y - r1.y) = r1.y - l1.y
            // Solve for s
            // t = (r1.x - l1.x + s(r2.x - r1.x)) / (l2.x - l1.x)
            // t = (r1.y - l1.y + s(r2.y - r1.y)) / (l2.y - l1.y)
            // (r1.x - l1.x + s(r2.x - r1.x)) / (l2.x - l1.x) = (r1.y - l1.y + s(r2.y - r1.y)) / (l2.y - l1.y)
            // (r1.x - l1.x)(l2.y - l1.y) + s(r2.x - r1.x)(l2.y - l1.y) = (r1.y - l1.y)(l2.x - l1.x) + s(r2.y - r1.y)(l2.x - l1.x)
            // s = ((r1.x - l1.x)(l2.y - l1.y) - (r1.y - l1.y)(l2.x - l1.x)) / ((r2.y - r1.y)(l2.x - l1.x) - (r2.x - r1.x)(l2.y - l1.y))
            // Plug s back into parametric equation to get x - intersection
            // x = r1.x + s(r2.x - r1.x)

            double s = ((r1.x - l1.x) * (l2.y - l1.y) - (r1.y - l1.y) * (l2.x - l1.x)) /
                       ((r2.y - r1.y) * (l2.x - l1.x) - (r2.x - r1.x) * (l2.y - l1.y));
            double x = r1.x + s * (r2.x - r1.x);

            if (x < midLine) {
                l = l->right;
            } else {
                r = r->left;
            }
        }
    }
    return {l, r};
}


int ConcatenableQueue::balanceFactor(ConcatenableQueue::QNode *&n) {
    return getHeight(n->left) - getHeight(n->right);
}

void ConcatenableQueue::inOrder(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return;
    inOrder(n->left);
    std::cout << n->angle << std::endl;
    inOrder(n->right);

}


void ConcatenableQueue::updateHeight(ConcatenableQueue::QNode *&n) {
    n->height = std::max(getHeight(n->left), getHeight(n->right)) + 1;
}

/**
 * @brief Splits the tree rooted at T into two parts, a tree of values lower than k, and a tree of values higher than k.
 * @param T - The tree to split
 * @param belongsToRight - A function that takes an angle and returns true if the angle belongs to the right tree.
 * @return The root of the left and right trees created by the division.
 */
std::pair<ConcatenableQueue::QNode *, ConcatenableQueue::QNode *>
ConcatenableQueue::split(ConcatenableQueue::QNode *T, bool (*belongsToRight)(Angle a)) {
    if (T == nullptr) {
        return {nullptr, nullptr};
    }
    if (belongsToRight(T->angle)) {
        // Moving left, know that T and everything right belongs to the Right tree
        auto [L, r] = split(T->left, belongsToRight);
        // Merge T->Right with the remaining nodes belonging to the right tree (r), using T as a middle value
        auto R = join(r, T, T->right);
        return {L, R};
    } else {
        auto [l, R] = split(T->right, belongsToRight);
        auto L = join(T->left, T, l);
        return {L, R};
    }

}

Angle *ConcatenableQueue::getMax(ConcatenableQueue::QNode *&n) {
    if (n == nullptr) return nullptr;
    if (n->right == nullptr) return &n->angle;
    return getMax(n->right);
}

Angle *ConcatenableQueue::getMin(ConcatenableQueue::QNode *&n) {
    if (n == nullptr) return nullptr;
    if (n->left == nullptr) return &n->angle;
    return getMin(n->left);
}

/**
 * @brief Removes the maximum value from the tree rooted at n.
 * @param n 
 * @return A pointer to the new root of the tree and a pointer to the removed node.
 * @details This function is simply a special case of split where every node belongs to the Left tree except the maximum
 */
std::pair<ConcatenableQueue::QNode *, ConcatenableQueue::QNode *>
ConcatenableQueue::removeMax(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return {nullptr, nullptr};
    if (n->right == nullptr) return {n->left, n};
    auto [L, r] = removeMax(n->right);
    return {join(n->left, n, L), r};
}

std::pair<ConcatenableQueue::QNode *, ConcatenableQueue::QNode *>
ConcatenableQueue::removeMin(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return {nullptr, nullptr};
    if (n->left == nullptr) return {n, n->right};
    auto [l, R] = removeMin(n->left);
    return {l, join(R, n, n->right)};
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
