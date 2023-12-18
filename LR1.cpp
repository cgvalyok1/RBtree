// LRtrue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "RBTree.h"

using namespace std;

int main()
{
    
    RedBlackTree tree1 = RedBlackTree();
    RedBlackTree tree2 = RedBlackTree();
    
    cout << " tree1 Adding" << endl;
    for (char i = 'A'; i <= 'Z'; i++)
    {
        tree1.insert(i);
    }
    tree1.printTree();
    
    cout << "tree1 Deleting" << endl;
    for (char i = 'A'; i <= 'Z' - 13; i=i+2)
    {   
        tree1.deleteNode(i);
    }
    tree1.printTree();

    cout << "tree1 - tree2 (tree2 empty)" << endl;
    tree1 = tree1 - tree2;
    tree1.printTree();

    cout << "tree2 Adding" << endl;
    for (char i = 'F'; i <= 'P'; i++)
    {
        tree2.insert(i);
    }
    tree2.printTree();

    RedBlackTree tree3 = RedBlackTree();

    cout << "tree3 = tree1 - tree2" << endl;
    tree3 = tree1 - tree2;
    tree3.printTree();

    cout << "tree3 = tree3 - tree3" << endl;
    tree3 = tree3 - tree3;
    tree3.printTree();

    

    
}
