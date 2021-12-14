//
// Created by 777 on 14.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_NODE_H
#define COURSEWORK_3_SEMESTER_NODE_H

#include "MiddleNode.h"

class Node : public MiddleNode {
public:
    Node();

    int count;
    char *str;
};


#endif //COURSEWORK_3_SEMESTER_NODE_H
