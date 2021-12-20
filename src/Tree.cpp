//
// Created by 777 on 14.12.2021.
//

#include "Tree.h"

Tree::Tree() {
    root = FNULL;
    level = 0;
    peakCount = 0;
}

Tree::Tree(char *name) : basic_fstream(name, ios::in | ios::out | ios::binary | ios::trunc) {
    root = FNULL;
    level = 0;
    peakCount = 0;
}


void Tree::insert(char *str) {
    FNode *node = readNode(root);
    addNode(node, root, str);
    peakCount++;
}

void Tree::update() {
    root = 0;
    level = 0;
    peakCount = 0;
}

ostream &operator<<(ostream &os, Tree &tree) {
    tree.printNode(tree.root, os);
    return os;
}

Tree &Tree::operator<<(char *str) {
    FNode *node = readNode(root);
    addNode(node, root, str);
    peakCount++;
    return *this;
}

Tree &Tree::operator<<(ifstream &is) {
    char buf[100];
    while (!is.eof()) {
        is >> buf;
        FNode *node = readNode(root);
        addNode(node, root, buf);
        peakCount++;
    }
    return *this;
}


//Node *Tree::GetTree(long pos) {
//    if (pos == FNULL) return nullptr;
//    Node *q = new Node;
//    FNode A;
//    seekg(pos);
//    read((char *) &A, sizeof(FNode));
//    q->strLen = A.strLen;
//    if (q->strLen == 0) {
//        q->str = nullptr;
//    } else {
//        q->str = new char[A.strLen];
//        read((char *) q->str, A.strLen * sizeof(char));
//        peakCount++;
//    }
//    q->peakCount = A.peakCount;
//    q->left = GetTree(A.left);
//    q->right = GetTree(A.right);
//
//    return q;
//}

//void Tree::LoadTree() {
//    if (peek() != std::ifstream::traits_type::eof()) {
//        long phead = FNULL;
//        read((char *) &phead, sizeof(long));
//        this->root = GetTree(phead);
//    }
//}

//istream &operator>>(istream &os, Tree &tree) {
//    tree.root = new Node;
//    os.read((char *) tree.root, sizeof(Node));
//    return os;
//}

//void Tree::createNode(Node **node, char *str) {
//    Node *newNode = new Node;
//    size_t len = strlen(str);
//    newNode->str = new char[len];
//    newNode->strLen = len;
//    newNode->peakCount = 0;
//    newNode->left = nullptr;
//    newNode->right = nullptr;
//    for (int i = 0; i < len; ++i) {
//        newNode->str[i] = str[i];
//    }
//    *node = newNode;
//}
long long Tree::createNode(char *str, size_t len) {
//    seekp(fstream::end);
    long long pos = tellp();
    FNode node(str, len);
    cout << "STRLEN " << node.strLen << endl;
//    write((char *) &node, sizeof(FNode));
    write((char *) &node.left, sizeof(long long));
    write((char *) &node.right, sizeof(long long));
    write((char *) &node.peakCount, sizeof(int));
    write((char *) &node.strLen, sizeof(size_t));
    write(node.str, node.strLen * sizeof(char));
    return pos;
}

void Tree::copyNode(long long pos_node, char *str, int mode) {
//    FNode newNode(node->str, node->strLen);
    FNode *curNode = readNode(pos_node);
    if (curNode == nullptr) return;
    long long pos = createNode(curNode->str, curNode->strLen);

//    write((char *) &newNode, sizeof(FNode));

//    Node *newNode = new Node;
//    size_t len = node->strLen;
//    newNode->str = new char[len];
//    newNode->strLen = len;
//    for (int i = 0; i < len; ++i) {
//        newNode->str[i] = node->str[i];
//    }
//    delete node->str;
//    node->str = nullptr;
//    node->strLen = 0;
//    node->peakCount = 2; // TODO delete old node
    long long newPos = createNode(str, strlen(str));
    seekp(pos_node);
    int m = 2;
    if (mode == 1) {
        write((char *) &pos, sizeof(long long));
        write((char *) &newPos, sizeof(long long));
//        node->left = pos;
//        node->right = createNode(str);
//        createNode(&node->right, str);
    } else if (mode == 2) {
        write((char *) &newPos, sizeof(long long));
        write((char *) &pos, sizeof(long long));
//        createNode(&node->left, str);
//        node->left = createNode(str);
//        node->right = pos;
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
        read((char *) &node->peakCount, sizeof(int));
        read((char *) &node->strLen, sizeof(size_t));
        node->str = new char[node->strLen];
        read(node->str, node->strLen * sizeof(char));
        seekg(0, fstream::end);
        return node;
    } else {
        return nullptr;
    }
}

void Tree::printNode(long long pos, ostream &os) {
    FNode *node = readNode(pos);
    if (node != nullptr) {
        if (node->peakCount == 0) {
            for (int i = 0; i < node->strLen; ++i) {
                os << node->str[i];
            }
            os << ' ';
        }
        printNode(node->left, os);
        printNode(node->right, os);
    }
}

//Node *Tree::findInd(Node *node, int *curInd, int needInd) {
//    if (node == nullptr) {
//        return nullptr;
//    }
//    if (*curInd == needInd && node->str != nullptr) {
//        return node;
//    }
//    if (node->str != nullptr) {
//        (*curInd)++;
//    }
//    Node *tmp = findInd(node->left, curInd, needInd);
//    if (!tmp)
//        tmp = findInd(node->right, curInd, needInd);
//    return tmp;
//}


//Node &Tree::operator[](int ind) {
//    int tmp = 0;
//    Node *node = findInd(root, &tmp, ind);
//    return *node;
//}

//int Tree::getSize() {
//    return peakCount;
//}



