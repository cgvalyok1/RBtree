#include "RBTree.h"
void RedBlackTree::inOrderHelper(NodePtr node)
{
    if (node != TNULL) {
        inOrderHelper(node->left);
        cout << node->data << " ";
        inOrderHelper(node->right);
    }
}
bool RedBlackTree::searchTreeHelper(NodePtr node, char key)
{
    if (node == TNULL)
    {
        return false;
    }
    if (key == node->data) 
    {
        return true;
    }

    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}
void RedBlackTree::deleteFix(NodePtr x)
{
    NodePtr s;
    while (x != root && x->is_red == false) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->is_red == true) {
                s->is_red = false;
                x->parent->is_red = true;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->is_red == false && s->right->is_red == false) {
                s->is_red = true;
                x = x->parent;
            }
            else {
                if (s->right->is_red == false) {
                    s->left->is_red = false;
                    s->is_red = true;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->is_red = x->parent->is_red;
                x->parent->is_red = false;
                s->right->is_red = false;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            s = x->parent->left;
            if (s->is_red == true) {
                s->is_red = false;
                x->parent->is_red = true;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->is_red == false && s->right->is_red == false) {
                s->is_red = true;
                x = x->parent;
            }
            else {
                if (s->left->is_red == false) {
                    s->right->is_red = false;
                    s->is_red = true;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->is_red = x->parent->is_red;
                x->parent->is_red = false;
                s->left->is_red = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->is_red = false;
}
void RedBlackTree::RBTransplant(NodePtr u, NodePtr v)
{
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}
void RedBlackTree::deleteNodeHelper(NodePtr node, char key)
{
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        cout << "Key not found in the tree" << endl;
        return;
    }

    y = z;
    bool y_original_is_red = y->is_red;
    if (z->left == TNULL) {
        x = z->right;
        RBTransplant(z, z->right);
    }
    else if (z->right == TNULL) {
        x = z->left;
        RBTransplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_is_red = y->is_red;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            RBTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        RBTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->is_red = z->is_red;
    }
    delete z;
    if (y_original_is_red == false) {
        deleteFix(x);
    }
}
void RedBlackTree::insertFix(NodePtr k)
{
    NodePtr u;
    while (k->parent->is_red == true) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->is_red == true) {
                u->is_red = false;
                k->parent->is_red = false;
                k->parent->parent->is_red = true;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->is_red = false;
                k->parent->parent->is_red = true;
                leftRotate(k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;

            if (u->is_red == true) {
                u->is_red = false;
                k->parent->is_red = false;
                k->parent->parent->is_red = true;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->is_red = false;
                k->parent->parent->is_red = true;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->is_red = false;
}
void RedBlackTree::printHelper(NodePtr root, string indent, bool last)
{
    if (root != TNULL) {
        printHelper(root->right, indent + "          ", true);
        cout << indent << root->data;
        if (root->parent == nullptr) {
            cout << "-(root-";
        }
        else if (last) {
            cout << "-(R-";
        }
        else {
            cout << "-(L-";
        }

        string sis_red = root->is_red ? "RED" : "BLACK";
        cout << sis_red << ")" << endl;
        printHelper(root->left, indent + "          ", false);
    }
}
void RedBlackTree::destory(NodePtr& node)
{
    if (node == TNULL)
        return;
    destory(node->left);
    destory(node->right);
    delete node;
    node = nullptr;
}
RedBlackTree operator - (const RedBlackTree& tree1, const RedBlackTree& tree2)
{
    RedBlackTree T(tree1);
    if (T.root != T.TNULL && tree2.root != tree2.TNULL)
    {
        T.DifHelper(tree2.root, tree2.TNULL);
    }
    return T;
}
void RedBlackTree::DifHelper(NodePtr root, NodePtr tnull)
{
    if (root != tnull)
    {
        deleteNode(root->data);
        DifHelper(root->left, tnull);
        DifHelper(root->right, tnull);
    }
}
RedBlackTree::RedBlackTree()
{
    TNULL = new Node;
    TNULL->is_red = false;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}
RedBlackTree::~RedBlackTree()
{
    destory(root);
}
RedBlackTree& RedBlackTree::operator = (const RedBlackTree& tree)
{
    if (this != &tree && tree.root != tree.TNULL)
    {
        this->~RedBlackTree();
        TNULL = tree.TNULL;
        root = TNULL;
        CopyHelper(tree.root);
    }
    else if (tree.root == tree.TNULL)
    {
        this->~RedBlackTree();
        root = TNULL;
    }
    return *this;
}

void RedBlackTree::CopyHelper(NodePtr node)
{
    if (node != TNULL)
    {
        insert(node->data);
        CopyHelper(node->left);
        CopyHelper(node->right);
    }
}
RedBlackTree::RedBlackTree(const RedBlackTree& tree)
{
    TNULL = new Node;
    TNULL = tree.TNULL;
    root = TNULL;
    CopyHelper(tree.root);
}
void RedBlackTree::inorder()
{
    inOrderHelper(this->root);
    cout << endl;
}
bool RedBlackTree::searchTree(char k)
{
    return searchTreeHelper(this->root, k);
}
NodePtr RedBlackTree::minimum(NodePtr node)
{
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}
void RedBlackTree::leftRotate(NodePtr x)
{
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void RedBlackTree::rightRotate(NodePtr x)
{
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}
void RedBlackTree::insert(char key)
{
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->is_red = true;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->data < y->data) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->is_red = false;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    insertFix(node);
}
NodePtr RedBlackTree::getRoot()
{
    return this->root;
}
void RedBlackTree::deleteNode(char data)
{
    deleteNodeHelper(this->root, data);
}
void RedBlackTree::printTree()
{
    cout << "------------------------------------------------------------------------" << endl;
    if (root != TNULL) {
        printHelper(this->root, "", true);
    }
    else {
        cout << "this tree is empty" << endl;
    }
    cout << "------------------------------------------------------------------------" << endl;
}