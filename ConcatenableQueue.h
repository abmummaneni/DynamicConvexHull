/**
 * @file ConcatenableQueue.h
 * @brief Concatenable Queue is a data structure that supports splitting and concatenation in O(log n) time.
 * @date 10/18/23
 * @author: Abhinav Mummaneni
 */

#ifndef DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
#define DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H

#include "Point.h"


class ConcatenableQueue {
public:
    ConcatenableQueue();

    ~ConcatenableQueue();

    void concatenate(ConcatenableQueue *q);
    
    void split(Point p, ConcatenableQueue *q1, ConcatenableQueue *q2);


};


#endif //DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
