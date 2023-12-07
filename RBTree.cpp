#include "RBTree.h"
using namespace std;

Node::Node(char key, bool is_red, Node* p, Node* l, Node* r)
{
    this->key = key;
    this->Is_Red = is_red;
    this->parent = p;
    this->left_child = l;
    this->right_child = r;
}

RBTree::RBTree(char key)
{
    this->root = new Node(key, false, nullptr, nullptr, nullptr);
}

RBTree::~RBTree()
{
    destory(root);
}

void RBTree::leftRotate(Node*& root, Node* x)
{
    Node* y = x->right_child;
    x->right_child = y->left_child;
    if (y->left_child != nullptr)
        y->left_child->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else {
        if (x == x->parent->left_child)
            x->parent->left_child = y;
        else
            x->parent->right_child = y;
    }
    y->left_child = x;
    x->parent = y;
}

void RBTree::rightRotate(Node*& root, Node* y)
{
    Node* x = y->left_child;
    y->left_child = x->right_child;
    if (x->right_child != nullptr)
        x->right_child->parent = y;

    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else {
        if (y == y->parent->right_child)
            y->parent->right_child = x;
        else
            y->parent->left_child = x;
    }
    x->right_child = y;
    y->parent = x;
}

void RBTree::destory(Node*& node)
{
    if (node != nullptr)
    {
        destory(node->left_child);
        destory(node->right_child);
        delete node;
        node = nullptr;
    }
}

