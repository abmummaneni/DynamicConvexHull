/**
 * @file TTree.cpp
 * @date 10/18/23
 * @author Abhinav Mummaneni
 * @details TTree is implemented via an augmented red-black tree. Each leaf node stores a Point, a Concatenable Queue, 
 * a pointer to the break point in the Concatenable Queue, and a pointer to the maximum value in the left subtree.
 */

#include "TTree.h"
#include <iostream>
#include <queue>
#include <cassert>
#include <cmath>
#include <algorithm>
using QNode = ConcatenableQueue::QNode;
/**
 * @brief Constructs a leaf node with the given point
 * @param p The point to be stored in the leaf node
 * @details The node is colored as black because the leaf nodes are always black in a red-black tree.
 * In this sense, the leaf nodes are analogous to the NIL nodes in a standard red-black tree.
 */
TTree::TNode::TNode(Point p, TTree::TNode *par = nullptr) {
    point = p;
    isLeaf = true;
    color = BLACK;
    left = right = nullptr;
    parent = par;
    lMax = rMin = this;
    lower_hull = new ConcatenableQueue(p, ConcatenableQueue::LOWER);
    upper_hull = new ConcatenableQueue(p, ConcatenableQueue::UPPER);
}

/**
 * @brief Constructs an internal node with the given parent, left child, and right child
 * @param par Parent node
 * @param l Left child
 * @param r Right child
 */
TTree::TNode::TNode(TTree::TNode *par, TTree::TNode *l, TTree::TNode *r) {
    isLeaf = false;
    color = RED;
    left = l;
    right = r;
    parent = par;
    lMax = l->rMin;
    rMin = r->lMax;
    l->parent = this;
    r->parent = this;
    lower_hull = new ConcatenableQueue(ConcatenableQueue::LOWER);
    upper_hull = new ConcatenableQueue(ConcatenableQueue::UPPER);
}

bool TTree::TNode::operator<(const TTree::TNode &rhs) const {
    return point < rhs.point;
}

bool TTree::TNode::operator>(const TTree::TNode &rhs) const {
    return rhs < *this;
}

bool TTree::TNode::operator<=(const TTree::TNode &rhs) const {
    return !(rhs < *this);
}

bool TTree::TNode::operator>=(const TTree::TNode &rhs) const {
    return !(*this < rhs);
}

/**
 * @brief Inserts a point into the tree rooted at curr
 * @param p The point to be inserted
 * @param curr The root of the tree to insert into
 * @details If curr is a leaf node, then a new internal node is created with curr and p as its children.
 * If curr is an internal node, the function is recursively called on the proper subtree until a leaf node is reached.
 */
TTree::TNode *TTree::insert(Point &p, TTree::TNode *curr) {
    if (curr == nullptr) {
        root = new TNode(p);
        return root;
    }
    if (curr->lMax->point == p or curr->rMin->point == p) return nullptr;
    if (curr->isLeaf) {
        if (curr->point == p){ return nullptr;}
        TNode *newLeaf = new TNode(p);
        TNode *newInternal;
        if (p < curr->point) {
            newInternal = new TNode(curr->parent, newLeaf, curr);
        } else {
            newInternal = new TNode(curr->parent, curr, newLeaf);
        }
        if (newInternal->parent == nullptr) {
            root = newInternal;
        } else if (newInternal->parent->left == curr) {
            newInternal->parent->left = newInternal;
        } else {
            newInternal->parent->right = newInternal;
        }

        fixUp(newInternal);
        return newLeaf;
    } else {
        descend(curr);
        if (p < curr->lMax->point) {
            return insert(p, curr->left);
        } else {
            if (p < curr->rMin->point) {
                TNode *newLeaf = insert(p, curr->right);
                curr->rMin = newLeaf;
                return newLeaf;
            } else {
                return insert(p, curr->right);
            }

        }
    }
}

TTree::TNode *TTree::remove(Point &p, TTree::TNode *n) {
    if (n->isLeaf) {
        if (n->point != p) {
            return nullptr;
        }
        if (n == root) {
            root = nullptr;
            delete n;
            return nullptr;
        }

        TNode *sibling;
        if (n->parent->left == n) {
            sibling = n->parent->right;
        } else {
            sibling = n->parent->left;
        }
        transplant(n->parent, sibling);

        if (n->parent->color == BLACK) {
            removeFixUp(sibling);
        }
        TNode *par = n->parent;
        delete n;
        return par;
        

    } else {
        descend(n);
        if (p == n->lMax->point){
            TNode *internalToDelete = remove(p, n->left);
            if (n != internalToDelete) {
                n->lMax = internalToDelete->lMax;
                delete internalToDelete; 
            } else {
                return internalToDelete;
            }
            
        }
        else if (p == n->rMin->point){
            TNode *internalToDelete = remove(p, n->right);
            if (n != internalToDelete){
                n->rMin = internalToDelete->rMin;
                delete internalToDelete;
            } else {
                return internalToDelete;
            }
            
        }
        else if (p < n->lMax->point) {
            return remove(p, n->left);
        } else {
            return remove(p, n->right);
        }
    }
}

/**
 * @brief Rotates the tree left about the node n
 * @param n the node at which the rotation occurs
 */
void TTree::rotateLeft(TTree::TNode *n) {
    descend(n);
    TNode *rightNode = n->right;
    descend(rightNode);

    if (n == root) {
        root = rightNode;
    } else if (n->parent->left == n) { // n is a left child
        n->parent->left = rightNode;
    } else {
        n->parent->right = rightNode;
    }
    rightNode->parent = n->parent;

    n->right = rightNode->left;
    if (rightNode->left != nullptr) {
        rightNode->left->parent = n;
    }

    rightNode->left = n;
    n->parent = rightNode;
    
}

/**
 * @brief Rotates the tree right about the node n, symmetric to rotateLeft, updates the root if necessary
 * @param n the node at which the rotation occurs
 */
void TTree::rotateRight(TTree::TNode *n) {
    descend(n);
    TNode *leftNode = n->left;
    descend(leftNode);

    transplant(n, leftNode);

    n->left = leftNode->right;
    if (leftNode->right != nullptr) {
        leftNode->right->parent = n;
    }

    leftNode->right = n;
    n->parent = leftNode;
}

void TTree::flipColors(TTree::TNode *n) {
    n->color = RED;
    n->left->color = BLACK;
    n->right->color = BLACK;
}

/**
 * @brief Fixes the red-black tree property after an insertion, based on the pseudocode from CLRS
 * @param curr 
 */
void TTree::fixUp(TTree::TNode *curr) {
    if (curr == root) {
        curr->color = BLACK;
        return;
    }

    while (curr->parent != nullptr and curr->parent->color == RED) {
        TNode *par = curr->parent;
        TNode *grandPar = par->parent; // par being red ==> par not the root ==> grandPar exists, and is black
        if (grandPar->left == par) {   // par is a left child
            TNode *uncle = grandPar->right;
            if (uncle->color == RED) {  // case 1 Red Parent, Red Uncle
                flipColors(grandPar);   // Transfer Blackness from Grandparent to Parent and Uncle
                curr = grandPar;        // Move up two levels
            } else {
                if (par->right == curr) { // case 2 Red Parent, Black Uncle, Inner GrandChild 
                    rotateLeft(par);      // Rotate to make case 3
                    curr = par;           // Par has moved down one level so curr is now par
                    par = curr->parent;
                }
                // case 3 Red Parent, Black Uncle, Outer GrandChild
                rotateRight(grandPar);    // Make Par the new root of the subtree
                par->color = BLACK;       // Swap colors of Par and Grandparent
                grandPar->color = RED;
            }
        } else {                          // par is a right child, symmetric to above
            TNode *uncle = grandPar->left;
            if (uncle->color == RED) {
                flipColors(grandPar);
                curr = grandPar;
            } else {
                if (par->left == curr) {
                    rotateRight(par);
                    curr = par;
                    par = curr->parent;
                }
                rotateLeft(grandPar);
                par->color = BLACK;
                grandPar->color = RED;
            }
        }
    }
    root->color = BLACK;
}

bool TTree::insert(Point p) {
    TNode *newLeaf = insert(p, root);
    ascend(root);
    return newLeaf != nullptr;
}

bool TTree::remove(Point p) {
    bool found = remove(p, root);
    ascend(root);
    return found;
}

// Pretty Prints all the Internal and Leaf nodes as they would appear in the tree with proper formatting and spacing.
// Each point's x coordinate is printed and each internal node is printed as I.
// The proper white space to be printed between nodes is calculated by the level and nodes are printed by their red or black color
void TTree::displayTree() {
    if (root == nullptr) {
        std::cout << "Empty Tree" << std::endl;
        return;
    }
    std::queue<TNode *> q;
    q.push(root);
    int level = 0;
    bool keepGoing = true;
    while (!q.empty() and keepGoing) {
        keepGoing = false;
        int size = q.size();
        std::cout << "Level " << level << ":";
        std::cout << std::string(ceil(pow(2, (7 - level))), ' ');
        for (int i = 0; i < size; i++) {
            TNode *n = q.front();
            q.pop();
            if (n == nullptr) {
                std::cout << "N ";
                q.push(nullptr);
                q.push(nullptr);
                std::cout << std::string(abs(pow(2, (8 - level)) - 2), ' ');
                continue;
            }
            if (n->isLeaf) {
                keepGoing = true;
                if (n->color == RED) std::cout << "\033[1;31m";
                else std::cout << "\033[1;30m";
                std::cout << n->point.x;
                std::cout << "\033[0m";
            } else {
                keepGoing = true;
                if (n->color == RED) std::cout << "\033[1;31m";
                else std::cout << "\033[1;30m";
                std::cout << "I ";
                std::cout << "\033[0m";
            }
            q.push(n->left);
            q.push(n->right);
            std::cout << std::string(pow(2, (8 - level)) - 2, ' ');
        }
        std::cout << std::endl;
        level++;
    }
}

TTree::TTree() {
    root = nullptr;
}

TTree::~TTree() {
    recycle(root);
}

void TTree::recycle(TTree::TNode *n) {
    if (n == nullptr) return;
    recycle(n->left);
    recycle(n->right);
    delete n;
}

void TTree::transplant(TTree::TNode *u, TTree::TNode *v) {
    if (u == root) {
        root = v;
    } else if (u->parent->left == u) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }

}


void TTree::removeFixUp(TTree::TNode *curr) {
    while (curr != root and curr->color == BLACK) {
        TNode *par = curr->parent;
        if (par->left == curr) {
            TNode *sibling = par->right;
            if (sibling->color == RED) { // case 1
                sibling->color = BLACK;
                par->color = RED;
                rotateLeft(par);
                sibling = par->right;
            }
            if (sibling->left->color == BLACK and sibling->right->color == BLACK) { // case 2
                sibling->color = RED;
                curr = par;
            } else {
                if (sibling->right->color == BLACK) { // case 3
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    descend(sibling);
                    rotateRight(sibling);
                    
                    sibling = par->right;
                }
                sibling->color = par->color; // case 4
                par->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(par);
                curr = root;
            }
        } else {
            TNode *sibling = par->left;
            if (sibling->color == RED) { // case 1
                sibling->color = BLACK;
                par->color = RED;
                rotateRight(par);
                sibling = par->left;
            }
            if (sibling->left->color == BLACK and sibling->right->color == BLACK) { // case 2
                sibling->color = RED;
                curr = par;
            } else {
                if (sibling->left->color == BLACK) { // case 3
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    descend(sibling);
                    rotateLeft(sibling);
                    sibling = par->left;
                }
                sibling->color = par->color; // case 4
                par->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(par);
                curr = root;
            }
        }
    }
    curr->color = BLACK;
}

/*
 * recursively checks that the tree follows all red black tree properties and checks that rmin and lmax are correct
 */
int TTree::checkProperties(TTree::TNode *n) {
    if (n->isLeaf) {
        assert(n->color == BLACK);
        return 1;
    }
    if (n->color == RED) {
        assert(n->left->color == BLACK);
        assert(n->right->color == BLACK);
    }
    assert(n->lMax->point == findMax(n->left)->lMax->point);
    assert(n->rMin->point == findMin(n->right)->rMin->point);
    int leftBlackHeight = checkProperties(n->left);
    int rightBlackHeight = checkProperties(n->right);
    assert(leftBlackHeight == rightBlackHeight);
    if (n->color == BLACK) {
        return leftBlackHeight + 1;
    } else {
        return leftBlackHeight;
    }
}

void TTree::checkProperties() {
    if (root == nullptr) return;
    checkProperties(root);
}

TTree::TNode *TTree::findMax(TTree::TNode *n) {
    if (n->isLeaf) {
        return n;
    }
    return findMax(n->right);
}


TTree::TNode *TTree::findMin(TTree::TNode *n) {
    if (n->isLeaf) {
        return n;
    }
    return findMin(n->left);
}

void TTree::ascend(TTree::TNode *&n) {
    if (n->isLeaf or n->lower_hull->root != nullptr) {
        return;
    }
    if (n->left->lower_hull->root == nullptr) {
        ascend(n->left);
        assert(n->left->lower_hull->root != nullptr);
    }
    if (n->right->lower_hull->root == nullptr) {
        ascend(n->right);
        assert(n->right->lower_hull != nullptr);
    }
    assert(n->left->lower_hull->root != nullptr);
    assert(n->right->lower_hull->root != nullptr);
    n->lower_hull->mergeHulls(n->left->lower_hull, n->right->lower_hull);
    n->upper_hull->mergeHulls(n->left->upper_hull, n->right->upper_hull);
}


void TTree::printLowerHull() {
    ConcatenableQueue::inOrder(root->lower_hull->root);
}

std::vector<Point> TTree::getLowerHull() {
    std::vector<Point> points;
    ConcatenableQueue::getPoints(root->lower_hull->root, points);
    return points;
}
std::vector<Point> TTree::getUpperHull() {
    std::vector<Point> points;
    ConcatenableQueue::getPoints(root->upper_hull->root, points);
    return points;
}
std::vector<Point> TTree::getHull() {
    std::vector<Point> lower = getLowerHull();
    std::vector<Point> upper = getUpperHull();
    std::reverse(upper.begin(), upper.end()); // now upper is counterclockwise
    if (lower.empty()){
        return upper; 
    }
    if (upper.empty()){
        return lower;
    }
    if (upper.front() == lower.back()) {
        lower.pop_back();
    }
    if (lower.front() == upper.back()) {
        upper.pop_back();
    }
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}


void TTree::descend(TTree::TNode *&n) {
    if (n->isLeaf or n->lower_hull->root == nullptr) {
        return;
    }
    ConcatenableQueue *lChildHull = n->left->lower_hull; 
    ConcatenableQueue *rChildHull = n->right->lower_hull;
    n->lower_hull->splitHull(lChildHull, rChildHull);

    lChildHull = n->left->upper_hull;
    rChildHull = n->right->upper_hull;
    n->upper_hull->splitHull(lChildHull, rChildHull);
}


bool TTree::insert(double x, double y) {
    return insert(Point(x,y));
}

