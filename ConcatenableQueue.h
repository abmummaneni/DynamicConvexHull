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

class ConcatenableQueue {
private:
    std::vector<Point> hull;
public:
    ConcatenableQueue();
    explicit ConcatenableQueue(Point p);
    ~ConcatenableQueue();

    void concatenate(ConcatenableQueue *left, ConcatenableQueue *right);
    
    void split(Point *p, ConcatenableQueue *&left, ConcatenableQueue *&right);


};


#endif //DYNAMICCONVEXHULL_CONCATENABLEQUEUE_H
