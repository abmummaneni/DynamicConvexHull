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
private:
    struct QNode{
        Angle angle;
        QNode *left;
        QNode *right;
        int height;
    };
    std::vector<Angle> hull;
    Angle *bridge;
    QNode *root;
    void split(QNode *&k);
    QNode *join2(QNode *&T1, QNode *&T1Max, QNode *&T2Min, QNode *&T2);
    QNode *join(QNode *&T1, QNode *&bridge,  QNode *&T2);
    
    
    QNode* removeMax(QNode *&n);
    QNode* removeMin(QNode *&n);
    
    int height(QNode *&n);
    int balanceFactor(QNode *&n);
    
    QNode *rotateLeft(QNode *n);
    QNode *rotateRight(QNode *n);
public:
    ConcatenableQueue();
    explicit ConcatenableQueue(Point p);
    ~ConcatenableQueue();

    void concatenate(ConcatenableQueue *left, ConcatenableQueue *right);
    
    void splitHull(ConcatenableQueue *&left, ConcatenableQueue *&right);
    
    void findBridge(ConcatenableQueue *left, ConcatenableQueue *right);
    


};


#endif //DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
