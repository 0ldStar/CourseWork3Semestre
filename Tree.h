//
// Created by 777 on 14.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_TREE_H
#define COURSEWORK_3_SEMESTER_TREE_H

#include "MiddleNode.h"
#include "Node.h"
#include <fstream>
#include <iostream>

using namespace std;

class Tree {
public:
    Tree();

    Tree(Tree &a);

    friend ostream &operator<<(ostream &os, char *str);

    friend ostream &operator>>(ostream &os, char *str);

private:
    MiddleNode *root;
    int level;
    int peakCount;
};


#endif //COURSEWORK_3_SEMESTER_TREE_H
