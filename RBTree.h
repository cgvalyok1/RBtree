#pragma once
#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* parent;
    Node* left;
    Node* right;
    bool is_red;
};

typedef Node* NodePtr;

class RedBlackTree {
    friend RedBlackTree operator - (const RedBlackTree& tree1, const RedBlackTree& tree2);
private:
    NodePtr root;
    NodePtr TNULL;

    void inOrderHelper(NodePtr node);
    bool searchTreeHelper(NodePtr node, char key);
    void deleteFix(NodePtr x);
    void RBTransplant(NodePtr u, NodePtr v);
    void deleteNodeHelper(NodePtr node, char key);
    void insertFix(NodePtr k);
    void printHelper(NodePtr root, string indent, bool last);
    void destory(NodePtr& root);
    void CopyHelper(NodePtr node);
    void DifHelper(NodePtr root, NodePtr tnull);

public:

    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree& tree);
    RedBlackTree& operator = (const RedBlackTree& tree);
    void inorder();
    bool searchTree(char k);
    NodePtr minimum(NodePtr node);
    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);
    void insert(char key);
    NodePtr getRoot();
    void deleteNode(char data);
    void printTree();
};

