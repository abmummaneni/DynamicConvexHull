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
        
        QNode(Angle a);
        QNode(QNode *l,  Angle a, QNode *r);
        QNode() = default;

    };
    std::vector<Angle> hull;
    Angle *leftBridge;
    Angle *rightBridge;
    QNode *root;
    
    
    void split(QNode *&k);
    QNode *join2(QNode *&T1, QNode *&T1Max, QNode *&T2Min, QNode *&T2);
    QNode *join(QNode *&T1, Angle &k,  QNode *&T2);
    QNode *joinRight(QNode *&T1, Angle &k, QNode *&T2);
    QNode *joinLeft(QNode *&T1, Angle &k, QNode *&T2);
    static int getHeight(QNode *&n);
    static int balanceFactor(QNode *&n);
    
    
    QNode* removeMax(QNode *&n);
    QNode* removeMin(QNode *&n);
    
    
    
    QNode *rotateLeft(QNode *n);
    QNode *rotateRight(QNode *n);
    int checkHeight(QNode *n);
    void checkProperties(QNode *n, QNode *max, QNode *min);
public:
    ConcatenableQueue();
    explicit ConcatenableQueue(Point p);
    ~ConcatenableQueue();

    void concatenate(ConcatenableQueue *left, ConcatenableQueue *right);
    
    void splitHull(ConcatenableQueue *&left, ConcatenableQueue *&right);
    
    void findBridge(ConcatenableQueue *left, ConcatenableQueue *right);
    

};


#endif //DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
