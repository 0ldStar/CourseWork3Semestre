//
// Created by 777 on 16.12.2021.
//

#include "FNode.h"

FNode::FNode() {
    peakCount = 0;
    left = FNULL;
    right = FNULL;
    strLen = 0;
}

FNode::FNode(const char *_str, size_t len) {
    peakCount = 0;
    left = FNULL;
    right = FNULL;
    strLen = len;
    for (int i = 0; i < len; ++i) {
        str[i] = _str[i];
    }
}
