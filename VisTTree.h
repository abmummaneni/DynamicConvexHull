/**
 * @file VisTTree.h
 * @brief A child class of TTree that visualizes the tree by overriding the ascend and descend methods.
 */

#ifndef DYNAMICCONVEXHULL_VISTTREE_H
#define DYNAMICCONVEXHULL_VISTTREE_H


#include "TTree.h"
#include "VisUtils.h"

class VisTTree : public TTree {
    public:
    void ascend(TNode *&n) override;
    void descend(TNode *&n) override;
    void setVisUtils(VisUtils *visUtils);
    VisUtils *visUtils;
    bool insert(Point p) override;
    bool remove(Point p) override;
    void setVisualize(bool _visualize);
    void drawHullGraph(TNode *n);
private:
    bool visualize = true;
    
    
};


#endif //DYNAMICCONVEXHULL_VISTTREE_H
