//
// Created by 777 on 14.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_TREE_H
#define COURSEWORK_3_SEMESTER_TREE_H

#include "MiddleNode.h"
#include "Node.h"
#include "FNode.h"
#include <fstream>
#include <iostream>
#include <cstring>
//#pragma pack (pop)
using namespace std;

class Tree : public fstream {
public:
    Tree();

    Tree(Tree &a);

    ~Tree();

    void free();

    void toBinary();

    void LoadTree();

    Node &operator[](int ind);
//    void printTree();

    void insert(char *str);

    void update();

    friend ostream &operator<<(ostream &os, Tree &tree);

    Tree &operator<<(char *str);

//    Tree &operator>>(ostream &of);

    Tree &operator<<(ifstream &is);

    friend istream &operator>>(istream &os, Tree &tree);

    int getSize();

private:
    long long PutTree(Node *q);

    Node *findInd(Node *node, int *curInd, int needInd);

    Node *GetTree(long long pos);

    int addNode(Node **node, char *str);

    void freeNode(Node *node);

    void copyNode(Node *node, char *str, int mode);

    int checkNode(Node **node, char *str);

    void createNode(Node **node, char *str);

    void printNode(Node *node, ostream &os);

    Node *root;
    int level;
    int peakCount;
};


#endif //COURSEWORK_3_SEMESTER_TREE_H
