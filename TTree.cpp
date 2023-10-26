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

/**
 * @brief Constructs a leaf node with the given point
 * @param p The point to be stored in the leaf node
 * @details The node is colored as black because the leaf nodes are always black in a red-black tree.
 * In this sense, the leaf nodes are analogous to the NIL nodes in a standard red-black tree.
 */
TTree::TNode::TNode(Point p) {
    point = p;
    isLeaf = true;
    color = BLACK;
    left = right = nullptr;
    parent = nullptr;
    lMax = rMin = &point;
}

TTree::TNode::TNode(TTree::TNode *par, TTree::TNode *l, TTree::TNode *r) {
    isLeaf = false;
    color = RED;
    left = l;
    right = r;
    parent = par;
    lMax = l->lMax;
    rMin = r->rMin;
    l->parent = r->parent = this;
}

void TTree::insert(Point &p, TTree::TNode *&n) {
    if (n == nullptr) {
        root = new TNode(p);
        return;
    }
    if (n->isLeaf) {
        if (p < n->point) {
            n = new TNode(n->parent, new TNode(p), n);
            return fixUp(n);
        } else {
            n = new TNode(n->parent, n, new TNode(p));
            return fixUp(n);
        }
    } else {
        if (p < *(n->lMax)) {
            insert(p, n->left);
        } else {
            insert(p, n->right);
        }
    }
}

void TTree::remove(Point &p, TTree::TNode *n) {
    if (n->isLeaf) {
        if (n->point == p) {
            if (n == root) {
                root = nullptr;
                delete n;
                return;
            } else if (n->parent->left == n) {
                TNode *sibling = n->parent->right;
            } else {
                TNode *sibling = n->parent->left;
            }
            // replace n.parent with sibling and then delete parent and n
            if (n->parent == root) {

            }
            delete n;
            return;
        }
    } else {
        if (p < *(n->lMax)) {
            remove(p, n->left);
        } else {
            remove(p, n->right);
        }
    }
}

/**
 * @brief Rotates the tree left about the node n
 * @param n the node at which the rotation occurs
 */
void TTree::rotateLeft(TTree::TNode *n) {
    TNode *rightNode = n->right;

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
    TNode *leftNode = n->left;

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

void TTree::insert(Point p) {
    insert(p, root);
}

void TTree::remove(Point p) {
    remove(p, root);
}

// Pretty Prints all the Internal and Leaf nodes as they would appear in the tree with proper formatting and spacing.
// Each point's x coordinate is printed and each internal node is printed as I.
// The proper white space to be printed between nodes is calculated by the level and nodes are printed by their red or black color
void TTree::displayTree() {
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
