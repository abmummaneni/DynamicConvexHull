/**
 * @file ConcatenableQueue.cpp
 * @date 10/18/23
 * @author Abhinav Mummaneni
 * @details Concatenable Queue is implemented as a height balanced binary tree.
 */
 
#include "ConcatenableQueue.h"

ConcatenableQueue::ConcatenableQueue() = default;

ConcatenableQueue::~ConcatenableQueue() = default;

void ConcatenableQueue::concatenate(ConcatenableQueue *left, ConcatenableQueue *right) {

}

void ConcatenableQueue::split(Point *p, ConcatenableQueue *&left, ConcatenableQueue *&right) {

}

ConcatenableQueue::ConcatenableQueue(Point p) {
    hull.push_back(p);
}
