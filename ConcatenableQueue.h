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
    Angle *leftBridge;
    Angle *rightBridge;
    QNode *root;


    static std::pair<QNode *, QNode *> split(QNode *T, bool (*belongsToRight)(Angle a));

    QNode *join2(QNode *&T1, QNode *&T1Max, QNode *&T2Min, QNode *&T2);

    static QNode *join(QNode *T1, QNode *k, QNode *T2);

    static QNode *joinRight(QNode *T1, QNode *k, QNode *T2);

    static QNode *joinLeft(QNode *T1, QNode *k, QNode *T2);

    static int getHeight(QNode *&n);
    
    static Angle *getMax(QNode *&n);
    static Angle *getMin(QNode *&n);

    static int balanceFactor(QNode *&n);

    static void inOrder(QNode *n);

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

    void concatenate(ConcatenableQueue *left, ConcatenableQueue *right);

    void splitHull(ConcatenableQueue *&left, ConcatenableQueue *&right);

    std::pair<QNode *, QNode *> findBridge(ConcatenableQueue *left, ConcatenableQueue *right);


};


#endif //DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
