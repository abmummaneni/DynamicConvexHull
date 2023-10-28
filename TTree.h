/**
 * @file TTree.h
 * @brief TTree is a height balanced binary search tree that stores unprocessed data in its leaves and stores processed 
 * results in its internal nodes. The TTree helps solve the dynamic convex hull problem by storing the partially 
 * constructed convex hulls in the internal nodes and the points of the set in the leaves.
 * @date 10/18/23
 * @author Abhinav Mummaneni
 */

#ifndef DYNAMICCONVEXHULL_TTREE_H
#define DYNAMICCONVEXHULL_TTREE_H
#include "Point.h"
#include "ConcatenableQueue.h"

class TTree {
private:
    static const bool RED = false;
    static const bool BLACK = true;
    struct TNode {
        Point point;
        ConcatenableQueue *lower_hull;
        ConcatenableQueue *upper_hull;
        Point *breakPoint;
        bool isLeaf; 
        
        bool color;
        TNode *left;
        TNode *right;
        TNode *parent = nullptr;
        Point *lMax;
        Point *rMin;
        
        
        TNode(Point p, TNode *par);
        TNode(TNode* par, TNode *l, TNode *r);
        
    };
    TNode *root;
    
    void split(TNode *&n);
    void merge(TNode *&n);
    
    void insert(Point &p, TNode *&n);
    void remove(Point &p, TNode *n);
    void rotateLeft(TNode *n);
    void rotateRight(TNode *n);
    static void flipColors(TNode *n);
    void fixUp(TNode *curr);
    void transplant(TNode *u, TNode *v);
    
    void recycle(TNode *n);
public:
    TTree();
    ~TTree();
    void insert(Point p);
    void remove(Point p);
    void displayTree();
    
};


#endif //DYNAMICCONVEXHULL_TTREE_H
