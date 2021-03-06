//
// Created by 777 on 14.12.2021.
//

#include "Tree.h"

Tree::Tree() {
    root = FNULL;
    peakCount = 0;
}

Tree::Tree(char *name) : basic_fstream(name, ios::in | ios::out | ios::binary) {
    if (!is_open()) {
        open(name, ios::in | ios::out | ios::binary | ios::trunc);
        root = FNULL;
        peakCount = 0;
        write((char *) &peakCount, sizeof(int));
    } else {
        seekg(0, fstream::end);
        if (tellg() == 0) {
            clear();
            root = FNULL;
            peakCount = 0;
            write((char *) &peakCount, sizeof(int));
            cout << "EMPTY\n";

        } else {
            seekg(0, ios::beg);
            root = 4;
            read((char *) &peakCount, sizeof(int));
        }
    }
}


void Tree::insert(char *str) {
    FNode *node = readNode(root);
    addNode(node, root, str);
    peakCount++;
    updatePeakCount();
}

void Tree::updatePeakCount() {
    seekp(0, ios::beg);
    write((char *) &peakCount, sizeof(int));
    seekp(0, ios::end);
}

void Tree::update() {
    root = 4;
    peakCount = 0;
    seekp(0, ios::beg);
    write((char *) &peakCount, sizeof(int));
}

ostream &operator<<(ostream &os, Tree &tree) {
    tree.printNode(tree.root, os);
    return os;
}

Tree &Tree::operator<<(char *str) {
    if (strlen(str) <= MAXLEN)
        insert(str);
    else throw out_of_range("charLimit");
    return *this;
}

Tree &Tree::operator<<(ifstream &is) {
    char buf[100];
    while (!is.eof()) {
        is >> buf;
        if (strlen(buf) <= MAXLEN)
            insert(buf);
        else throw out_of_range("charLimit");
    }
    return *this;
}

long long Tree::createNode(char *str, size_t len) {
    seekp(0, ios::end);
    long long pos = tellp();
    FNode node(str, len);
    write((char *) &node.left, sizeof(long long));
    write((char *) &node.right, sizeof(long long));
    write((char *) &node.childCount, sizeof(int));
    write((char *) &node.strLen, sizeof(size_t));
    write(node.str, MAXLEN * sizeof(char));
    return pos;
}

void Tree::copyNode(long long posNode, char *str, int mode) {
    FNode *curNode = readNode(posNode);
    if (curNode == nullptr) return;
    int null = 0;
    seekp(posNode + 2 * sizeof(long long) + sizeof(int));
    write((char *) &null, sizeof(size_t));
    seekp(0, ios::end);
    long long pos = createNode(curNode->str, curNode->strLen);
    long long newPos = createNode(str, strlen(str));
    seekp(posNode);
    int m = 2;
    if (mode == 1) {
        write((char *) &pos, sizeof(long long));
        write((char *) &newPos, sizeof(long long));
    } else if (mode == 2) {
        write((char *) &newPos, sizeof(long long));
        write((char *) &pos, sizeof(long long));
    }
    write((char *) &m, sizeof(int));
    seekp(0, fstream::end);
}

int Tree::checkNode(FNode *node, long long &pos, char *str) {
    int status = 1;
    if (node == nullptr) {
        pos = createNode(str, strlen(str));
    } else if (node->left == FNULL) {
        copyNode(pos, str, 1);
    } else if (node->right == FNULL) {
        copyNode(pos, str, 2);
    } else {
        status = 0;
    }
    return status;
}

int Tree::addNode(FNode *node, long long &pos, char *str) {
    int status = 1;
    if (checkNode(node, pos, str)) {
    } else if (checkNode(readNode(node->left), node->left, str)) {
    } else if (checkNode(readNode(node->right), node->right, str)) {
    } else {
        if (checkNode(readNode(readNode(node->left)->left), readNode(node->left)->left, str)) {
        } else if (checkNode(readNode(readNode(node->left)->right), readNode(node->left)->right, str)) {
        } else if (checkNode(readNode(readNode(node->right)->left), readNode(node->right)->left, str)) {
        } else if (checkNode(readNode(readNode(node->right)->right), readNode(node->right)->right, str)) {
        } else {
            if (addNode(readNode(node->left), node->left, str)) {
            } else if (addNode(readNode(node->right), node->right, str)) {
            } else { status = 0; }
        }
    }
    return status;
}

FNode *Tree::readNode(long long pos) {
    if (pos != FNULL) {
        auto *node = new FNode;
        seekg(pos);
        read((char *) &node->left, sizeof(long long));
        read((char *) &node->right, sizeof(long long));
        read((char *) &node->childCount, sizeof(int));
        read((char *) &node->strLen, sizeof(size_t));
        read(node->str, MAXLEN * sizeof(char));
        seekg(0, fstream::end);
        return node;
    } else {
        return nullptr;
    }
}

void Tree::printNode(long long pos, ostream &os) {
    FNode *node = readNode(pos);
    if (node != nullptr) {
        if (node->childCount == 0 && node->strLen != 0) {
            for (int i = 0; i < node->strLen; ++i) {
                os << node->str[i];
            }
            os << ' ';
        }
        printNode(node->left, os);
        printNode(node->right, os);
    }
}

long long Tree::findInd(long long pos, int *curInd, int needInd) {
    if (pos == FNULL) {
        return FNULL;
    }
    FNode *node = readNode(pos);
    if (*curInd == needInd && node->childCount == 0 && node->strLen != 0) {
        return pos;
    }
    if (node->childCount == 0 && node->strLen != 0) {
        (*curInd)++;
    }
    long long tmp = findInd(node->left, curInd, needInd);
    if (tmp == FNULL)
        tmp = findInd(node->right, curInd, needInd);
    return tmp;
}

FNode &Tree::operator[](int ind) {
    int tmp = 0;
    long long pos = findInd(root, &tmp, ind);
    FNode *node = readNode(pos);
    return *node;
}

int Tree::getSize() const {
    return peakCount;
}

void Tree::editStr(int ind, const char *str, size_t len) {
    int tmp = 0;
    long long pos = findInd(root, &tmp, ind);
    seekp(pos + 2 * sizeof(long long) + sizeof(int));
    write((char *) &len, sizeof(size_t));
    write(str, len * sizeof(char));
    seekp(0, ios::end);
    if (len == 0) {
        peakCount--;
        updatePeakCount();
    }
}

