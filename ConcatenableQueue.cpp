/**
 * @file ConcatenableQueue.cpp
 * @date 10/18/23
 * @author Abhinav Mummaneni
 * @details Concatenable Queue is implemented as an AVL tree that uses the splitHull and join2 functions.
 */
 
#include "ConcatenableQueue.h"

ConcatenableQueue::ConcatenableQueue() = default;

ConcatenableQueue::~ConcatenableQueue() = default;

void ConcatenableQueue::concatenate(ConcatenableQueue *left, ConcatenableQueue *right) {

}

void ConcatenableQueue::splitHull(ConcatenableQueue *&left, ConcatenableQueue *&right) {

}

ConcatenableQueue::ConcatenableQueue(Point p) {
}

ConcatenableQueue::QNode *ConcatenableQueue::join2(QNode *&T1, QNode *&T1Max, QNode *&T2Min, QNode *&T2) {
}

/**
 * @brief Joins two trees together and uses the bridge to connect them. All values in T1 are less than the bridge 
 * which is less than all values in T2.
 * @param T1 
 * @param bridge 
 * @param T2 
 * @return A pointer to the new merged tree.
 */
ConcatenableQueue::QNode *ConcatenableQueue::join(ConcatenableQueue::QNode *&T1, ConcatenableQueue::QNode *&bridge,
                                                  ConcatenableQueue::QNode *&T2) {
    int height1 = T1->height;
    int height2 = T2->height;
}

