//
// Created by 777 on 14.12.2021.
//

#include "Tree.h"

Tree::Tree() {
    root = nullptr;
    level = 0;
    peakCount = 0;
}

Tree::~Tree() {
    freeNode(root);
}

void Tree::freeNode(Node *node) {
    if (node != nullptr) {
        freeNode(node->left);
        freeNode(node->right);
        delete node;
    }
}

void Tree::free() {
    freeNode(root);
    root = nullptr;
}

void Tree::insert(char *str) {
    addNode(&root, str);
    peakCount++;
}

void Tree::update() {
    root = nullptr;
    level = 0;
    peakCount = 0;
}

ostream &operator<<(ostream &os, Tree &tree) {
    tree.printNode(tree.root, os);
    return os;
}

Tree &Tree::operator<<(char *str) {
    addNode(&root, str);
    peakCount++;
    return *this;
}

Tree &Tree::operator<<(ifstream &is) {
    char buf[100];
    while (!is.eof()) {
        is >> buf;
        addNode(&root, buf);
        peakCount++;
    }
    return *this;
}


long Tree::PutTree(Node *q) {
    if (q == nullptr) return FNULL;
    FNode CUR;
    CUR.m = q->m;
    long pos;
    CUR.left = PutTree(q->left);
    CUR.right = PutTree(q->right);
    pos = tellp();
    CUR.strLen = q->strLen;
    write((char *) &CUR, sizeof(FNode));
    if (q->str) write(q->str, CUR.strLen * sizeof(char));
    return pos;
}


void Tree::toBinary() {
    if (root != nullptr) {
        long pos0 = FNULL;
        write((char *) &pos0, sizeof(long));
        pos0 = PutTree(root);
        seekp(std::fstream::beg);
        write((char *) &pos0, sizeof(long));
    }
}

Node *Tree::GetTree(long pos) {
    if (pos == FNULL) return nullptr;
    Node *q = new Node;
    FNode A;
    seekg(pos);
    read((char *) &A, sizeof(FNode));
    q->strLen = A.strLen;
    if (q->strLen == 0) {
        q->str = nullptr;
    } else {
        q->str = new char[A.strLen];
        read((char *) q->str, A.strLen * sizeof(char));
        peakCount++;
    }
    q->m = A.m;
    q->left = GetTree(A.left);
    q->right = GetTree(A.right);

    return q;
}

void Tree::LoadTree() {
    if (peek() != std::ifstream::traits_type::eof()) {
        long phead = FNULL;
        read((char *) &phead, sizeof(long));
        this->root = GetTree(phead);
    }
}

istream &operator>>(istream &os, Tree &tree) {
    tree.root = new Node;
    os.read((char *) tree.root, sizeof(Node));
    return os;
}

void Tree::createNode(Node **node, char *str) {
    Node *newNode = new Node;
    size_t len = strlen(str);
    newNode->str = new char[len];
    newNode->strLen = len;
    newNode->m = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    for (int i = 0; i < len; ++i) {
        newNode->str[i] = str[i];
    }
    *node = newNode;
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
    node->m = 2;
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

void Tree::printNode(Node *node, ostream &os) {
    if (node != nullptr) {
        if (node->str != nullptr) {
            for (int i = 0; i < node->strLen; ++i) {
                os << node->str[i];
            }
            os << ' ';
        }
        printNode(node->left, os);
        printNode(node->right, os);
    }
}

Node *Tree::findInd(Node *node, int *curInd, int needInd) {
    if (node == nullptr) {
        return nullptr;
    }
    if (*curInd == needInd && node->str != nullptr) {
        return node;
    }
    if (node->str != nullptr) {
        (*curInd)++;
    }
    Node *tmp = findInd(node->left, curInd, needInd);
    if (!tmp)
        tmp = findInd(node->right, curInd, needInd);
    return tmp;
}


Node &Tree::operator[](int ind) {
    int tmp = 0;
    Node *node = findInd(root, &tmp, ind);
    return *node;
}

int Tree::getSize() {
    return peakCount;
}



