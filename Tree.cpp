//
// Created by 777 on 14.12.2021.
//

#include "Tree.h"

Tree::Tree() {
    root = nullptr;
    level = 0;
    peakCount = 0;
}

Tree::Tree(Tree &a) {
    root = nullptr; // TODO
    level = a.level;
    peakCount = a.peakCount;
}

ostream &operator<<(ostream &os, char *str) {
    os << str;
    return os;
}

ostream &operator>>(ostream &os, char *str) {
    os << str;
    return os;
}