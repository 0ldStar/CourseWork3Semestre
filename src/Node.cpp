//
// Created by 777 on 14.12.2021.
//

#include "Node.h"

Node::Node() {
    strLen = 0;
    m = 0;
    str = nullptr;
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    if (!str) delete str;
}