/**
 * @file ConcatenableQueue.h
 * @brief Concatenable Queue is a data structure that supports splitting and concatenation in O(log n) time.
 * @date 10/18/23
 * @author: Abhinav Mummaneni
 */

#ifndef DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
#define DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H

#include "Point.h"
#include <vector>
#include "Angle.h"

class ConcatenableQueue {
public:
    struct QNode {
        Angle angle;
        QNode *left;
        QNode *right;
        int height;

        QNode(Angle a);

        QNode(QNode *l, Angle a, QNode *r);

        QNode() = default;

    };

    std::vector<Angle> hull;
    QNode *leftBridge = nullptr;
    QNode *rightBridge = nullptr;
    QNode *root;

    /**
    * @brief Splits the tree rooted at T into two parts, a tree of values lower than k, and a tree of values higher than k.
    * @param T - The tree to split
    * @param belongsToRight - A function that takes an angle and returns true if the angle belongs to the right tree.
    * @return The root of the left and right trees created by the division.
     */
    template<typename Functor>
    static std::pair<QNode *, QNode *> split(QNode *T, Functor belongsToRight){
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

    static QNode *join2(QNode *T1, QNode *T2);

    static QNode *join(QNode *T1, QNode *k, QNode *T2);

    static QNode *joinRight(QNode *T1, QNode *k, QNode *T2);

    static QNode *joinLeft(QNode *T1, QNode *k, QNode *T2);

    static int getHeight(QNode *&n);
    
    static QNode *getMax(QNode *n);
    static QNode *getMin(QNode *n);

    static int balanceFactor(QNode *&n);

    static void inOrder(QNode *n);
    
    static void getPoints(QNode *n, std::vector<Point> &points);

    static void updateHeight(QNode *&n);

    static std::pair<QNode *, QNode *> removeMax(QNode *n);
    static std::pair<QNode *, QNode *> removeMin(QNode *n);


    static QNode *rotateLeft(QNode *n);

    static QNode *rotateRight(QNode *n);

    static int checkHeight(QNode *n);

    static void checkProperties(QNode *n, QNode *max, QNode *min);

    ConcatenableQueue();

    explicit ConcatenableQueue(Point p);

    ~ConcatenableQueue();
    
    bool isLeaf(QNode *n);
    void concatenate(ConcatenableQueue *left, ConcatenableQueue *right);
    
    void mergeHulls(ConcatenableQueue *left, ConcatenableQueue *right);

    void splitHull(ConcatenableQueue *left, ConcatenableQueue *right);

    std::pair<QNode *, QNode *> findBridge(ConcatenableQueue *left, ConcatenableQueue *right);
    
    
    friend class TTree;
};


#endif //DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
