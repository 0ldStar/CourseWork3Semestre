//
// Created by 777 on 14.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_TREE_H
#define COURSEWORK_3_SEMESTER_TREE_H

#include "Node.h"
#include "FNode.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class Tree : public fstream {
public:
    Tree();

    explicit Tree(char *name);

//    void toBinary();

//    void LoadTree();

//    Node &operator[](int ind);
//    void printTree();

    void insert(char *str);

    void update();

    friend ostream &operator<<(ostream &os, Tree &tree);

    Tree &operator<<(char *str);

// //    Tree &operator>>(ostream &of);

    Tree &operator<<(ifstream &is);

//    friend istream &operator>>(istream &os, Tree &tree);

//    int getSize();

private:
//    long PutTree(Node *q);

//    Node *findInd(Node *node, int *curInd, int needInd);

//    Node *GetTree(long pos);

    int addNode(FNode *node, long long &pos, char *str);

//    void freeNode(Node *node);

    void copyNode(long long pos, char *str, int mode);

    int checkNode(FNode *node, long long &pos, char *str);

    long long createNode(char *str, size_t len);

    FNode *readNode(long long pos);

    void printNode(long long pos, ostream &os);

    long long root;
    int level;
    int peakCount;
};


#endif //COURSEWORK_3_SEMESTER_TREE_H
