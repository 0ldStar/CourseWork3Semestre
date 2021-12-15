//
// Created by 777 on 14.12.2021.
//

#include "Tree.h"

Tree::Tree() {
    root = nullptr;
    level = 0;
    peakCount = 0;
}

//Tree::~Tree() {
//    freeNode(root);
//}

//void Tree::freeNode(Node *node) {
//    if (node != nullptr) {
//        freeNode(node->left);
//        freeNode(node->right);
//        delete node;
//    }
//}


Tree::Tree(Tree &a) {
    root = nullptr; // TODO
    level = a.level;
    peakCount = a.peakCount;
}

void Tree::insert(char *str) {
    addNode(&root, str);
    peakCount++;
}

ostream &operator<<(ostream &os, const Tree &tree) {
    os.write((char *) tree.root, sizeof(Node));
    return os;
}

Tree &Tree::operator<<(char *str) {
    addNode(&root, str);
    peakCount++;
    return *this;
}

Tree &Tree::operator>>(Tree *copy) {

    return *this;
}


istream &operator>>(istream &os, Tree &tree) {
    tree.root = new Node;
    os.read((char *) tree.root, sizeof(Node));
    return os;
}

void Tree::createNode(Node **node, char *str) {
//    Node *newNode = new Node;
    Node tmp;
    write((char *) &tmp, sizeof(Node));
    Node *newNode = tellg();
    size_t len = strlen(str);
//    newNode.str = new char[len];
    char tmp[len];
    write((char *) tmp, len * sizeof(char));
    newNode.str = new char[len];
    newNode.strLen = len;
    for (int i = 0; i < len; ++i) {
        newNode.str[i] = str[i];
    }
    *node = &newNode;
}

void Tree::copyNode(Node *node, char *str, int mode) {
    Node *newNode = new Node;
    size_t len = node->strLen;
    newNode->str = new char[len];
    newNode->strLen = len;
    for (int i = 0; i < len; ++i) {
        newNode->str[i] = node->str[i];
    }
    delete node->str;
    node->str = nullptr;
    node->strLen = 0;
    if (mode == 1) {
        node->left = newNode;
        createNode(&node->right, str);
    } else if (mode == 2) {
        node->right = newNode;
        createNode(&node->left, str);
    }
}

int Tree::checkNode(Node **node, char *str) {
    int status = 1;
    Node *tmp = *node;
    if (tmp == nullptr) {
        createNode(&tmp, str);
    } else if (tmp->left == nullptr) {
        copyNode(tmp, str, 1);
    } else if (tmp->right == nullptr) {
        copyNode(tmp, str, 2);
    } else {
        status = 0;
    }
    *node = tmp;
    return status;
}

int Tree::addNode(Node **node, char *str) {
    int status = 1;
    Node *tmp = *node;
    if (checkNode(&tmp, str)) {
    } else if (checkNode(&tmp->left, str)) {
    } else if (checkNode(&tmp->right, str)) {
    } else {
        if (checkNode(&tmp->left->left, str)) {
        } else if (checkNode(&tmp->left->right, str)) {
        } else if (checkNode(&tmp->right->left, str)) {
        } else if (checkNode(&tmp->right->right, str)) {
        } else {
            if (addNode(&tmp->left, str)) {
            } else if (addNode(&tmp->right, str)) {
            } else { status = 0; }
        }
    }
    *node = tmp;
    return status;
}

void Tree::printNode(Node *node) {
    if (node != nullptr) {
        if (node->str != nullptr) {
            cout << node->str << ' ';
        }
        printNode(node->left);
        printNode(node->right);
    }
}

void Tree::printTree() {
    printNode(root);
}


