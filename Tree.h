//
// Created by 777 on 14.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_TREE_H
#define COURSEWORK_3_SEMESTER_TREE_H

#include "MiddleNode.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class Tree : public fstream {
public:
    Tree();

    Tree(Tree &a);

    ~Tree();

    void printTree();

    void insert(char *str);

    friend ostream &operator<<(ostream &os, const Tree &tree);

    friend istream &operator>>(istream &os, Tree &tree);

private:

    int addNode(Node **node, char *str);

    void freeNode(Node *node);

    void copyNode(Node *node, char *str, int mode);

    int checkNode(Node **node, char *str);

    void createNode(Node **node, char *str);

    void printNode(Node *node);

    Node *root;
    int level;
    int peakCount;
};


#endif //COURSEWORK_3_SEMESTER_TREE_H
