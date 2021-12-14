#include <iostream>
#include "MiddleNode.h"
#include "Node.h"

int main() {
    Node n1;
    Node n2;
    Node n3;
    MiddleNode m1;
    MiddleNode m2;
    MiddleNode m3;
    m1.right = &m2;
    m1.left = &m2;
    m1.right->right = &n1;
    m1.right->left = &n2;
    m1.left->right = &m3;
    m3.right = &n3;
    return 0;
}
