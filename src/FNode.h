//
// Created by 777 on 16.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_FNODE_H
#define COURSEWORK_3_SEMESTER_FNODE_H

#include <cstring>

#define FNULL (-1L)

class FNode {
public:
    FNode();

    FNode(const char *str, size_t len);

    ~FNode();

    int peakCount;
    long long left;
    long long right;
    size_t strLen;
    char *str;
};


#endif //COURSEWORK_3_SEMESTER_FNODE_H
