#pragma once
struct Node
{
    bool Is_Red;
    Node* parent;
    Node* left_child;
    Node* right_child;
    char key;
    Node(char key, bool is_red, Node* p, Node* l, Node* r);
};

class RBTree
{
private:
    Node* root;

    void leftRotate(Node* &root, Node* x);
    void rightRotate(Node* &root, Node* y);
    void destory(Node* &node);
public:
    RBTree(char key);
    ~RBTree();

};

