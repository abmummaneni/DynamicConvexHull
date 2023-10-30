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
        TNode *lMax;
        TNode *rMin;
        
        
        TNode(Point p, TNode *par);
        TNode(TNode* par, TNode *l, TNode *r);
        TNode() = default;

        bool operator<(const TNode &rhs) const;

        bool operator>(const TNode &rhs) const;

        bool operator<=(const TNode &rhs) const;

        bool operator>=(const TNode &rhs) const;

    };
    TNode *root;
    
    void split(TNode *&n);
    void merge(TNode *&n);
    
    TNode *insert(Point &p, TNode *curr);
    TNode *remove(Point &p, TNode *n);
    void rotateLeft(TNode *n);
    void rotateRight(TNode *n);
    static void flipColors(TNode *n);
    void fixUp(TNode *curr);
    void transplant(TNode *u, TNode *v);
    void removeFixUp(TNode *curr);
    
    int checkProperties(TNode *n);
    
    TNode *findMin(TNode *n);
    TNode *findMax(TNode *n);
    
    void recycle(TNode *n);
public:
    TTree();
    ~TTree();
    void insert(Point p);
    bool remove(Point p);
    void displayTree();
    void checkProperties();
    
};


#endif //DYNAMICCONVEXHULL_TTREE_H
