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

void ConcatenableQueue::splitHull(ConcatenableQueue *left, ConcatenableQueue *right) {
    auto [L, R] = split(root, [&](Angle a) { return a >= rightBridge->angle; });
    root = nullptr;
    if (left->root == nullptr) {
        left->root = L;
        leftBridge->angle.right = leftBridge->angle.middle;
        leftBridge->angle.right.y = INFINITY;
    } else {
        auto [leftFragmentMin, leftFragmentRoot] = removeMin(left->root);
        leftBridge->angle.right = leftFragmentMin->angle.middle;
        left->root = join(L, leftFragmentMin, leftFragmentRoot);
    }
    if (right->root == nullptr) {
        right->root = R;
        rightBridge->angle.left = rightBridge->angle.middle;
        rightBridge->angle.left.y = INFINITY;
    } else {
        auto [rightFragmentRoot, rightFragmentMax] = removeMax(right->root);
        rightBridge->angle.left = rightFragmentMax->angle.middle;
        right->root = join(rightFragmentRoot, rightFragmentMax, R);
    }

}

ConcatenableQueue::ConcatenableQueue(Point p) {
    root = new QNode(Angle(p));
}

ConcatenableQueue::QNode *ConcatenableQueue::join2(QNode *T1, QNode *T2) {
    if (T1 == nullptr) return T2;
    if (T2 == nullptr) return T1;
    int t1Height = getHeight(T1);
    int t2Height = getHeight(T2);
    if (t1Height > t2Height) {
        auto [_T1, middle] = removeMax(T1);
        return join(_T1, middle, T2);
    }
    auto [middle, _T2] = removeMin(T2);
    return join(T1, middle, _T2);

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
    assert(l != nullptr and r != nullptr);
    double maxLeft = getMax(l)->angle.middle.x;
    double minRight = getMin(r)->angle.middle.x;
    double midLine = 0.5 * (maxLeft + minRight);
    auto [lCase, rCase] = Angle::getCases(l->angle, r->angle);
    while (lCase != Supporting or rCase != Supporting) {
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

            /* Must find intersection of lines l1 l2 and r1 r2
             Create parametric equations
             l1 + t(l2 - l1) = r1 + s(r2 - r1)
             l1.x + t(l2.x - l1.x) = r1.x + s(r2.x - r1.x)
             l1.y + t(l2.y - l1.y) = r1.y + s(r2.y - r1.y)
             Create system with unknowns t and s
             t(l2.x - l1.x) - s(r2.x - r1.x) = r1.x - l1.x
             t(l2.y - l1.y) - s(r2.y - r1.y) = r1.y - l1.y
             Solve for s
             t = (r1.x - l1.x + s(r2.x - r1.x)) / (l2.x - l1.x)
             t = (r1.y - l1.y + s(r2.y - r1.y)) / (l2.y - l1.y)
             (r1.x - l1.x + s(r2.x - r1.x)) / (l2.x - l1.x) = (r1.y - l1.y + s(r2.y - r1.y)) / (l2.y - l1.y)
             (r1.x - l1.x)(l2.y - l1.y) + s(r2.x - r1.x)(l2.y - l1.y) = (r1.y - l1.y)(l2.x - l1.x) + s(r2.y - r1.y)(l2.x - l1.x)
             s = ((r1.x - l1.x)(l2.y - l1.y) - (r1.y - l1.y)(l2.x - l1.x)) / ((r2.y - r1.y)(l2.x - l1.x) - (r2.x - r1.x)(l2.y - l1.y))
             Plug s back into parametric equation to get x - intersection
             x = r1.x + s(r2.x - r1.x)
             */

            double s = ((r1.x - l1.x) * (l2.y - l1.y) - (r1.y - l1.y) * (l2.x - l1.x)) /
                       ((r2.y - r1.y) * (l2.x - l1.x) - (r2.x - r1.x) * (l2.y - l1.y));
            double x = r1.x + s * (r2.x - r1.x);

            if (x < midLine) {
                l = l->right;
            } else {
                r = r->left;
            }
        }
        assert(l != nullptr and r != nullptr);
        std::tie(lCase, rCase) = Angle::getCases(l->angle, r->angle);
    }
    if (l->angle.middle.x == r->angle.middle.x){
        return {getMax(l), getMin(r)};
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


ConcatenableQueue::QNode *ConcatenableQueue::getMax(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return nullptr;
    if (n->right == nullptr) return n;
    return getMax(n->right);
}

ConcatenableQueue::QNode *ConcatenableQueue::getMin(ConcatenableQueue::QNode *n) {
    if (n == nullptr) return nullptr;
    if (n->left == nullptr) return n;
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

void ConcatenableQueue::mergeHulls(ConcatenableQueue *left, ConcatenableQueue *right) {
    std::tie(leftBridge, rightBridge) = findBridge(left, right);
    Angle &leftBridgeAngle = leftBridge->angle;
    Angle &rightBridgeAngle = rightBridge->angle;
    auto [leftLeft, leftRight] = split(left->root, [&](Angle a) { return a > leftBridgeAngle; });
    auto [rightLeft, rightRight] = split(right->root, [&](Angle a) { return a >= rightBridgeAngle; });
    left->root = leftRight;
    right->root = rightLeft;
    leftBridgeAngle.right = rightBridgeAngle.middle;
    rightBridgeAngle.left = leftBridgeAngle.middle;
    root = join2(leftLeft, rightRight);
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

void ConcatenableQueue::getPoints(ConcatenableQueue::QNode *n, std::vector<Point> &points) {
    if (n == nullptr) return;
    getPoints(n->left, points);
    points.push_back(n->angle.middle);
    getPoints(n->right, points);
}


bool ConcatenableQueue::isLeaf(ConcatenableQueue::QNode *n) {
    return (n->left == nullptr and n->right == nullptr);
}
