//
// Created by 777 on 14.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_NODE_H
#define COURSEWORK_3_SEMESTER_NODE_H

#include <cstring>

class Node {
public:
    Node();

    ~Node();

    int m;
    Node *left;
    Node *right;
    size_t strLen;
    char *str;
};

#endif //COURSEWORK_3_SEMESTER_NODE_H
