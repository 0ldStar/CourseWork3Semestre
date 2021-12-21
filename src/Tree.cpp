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
        cout << "REOPEN\n";
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
    cout << "POSG " << tellg() << endl;
    cout << "POSP " << tellp() << endl;
}


void Tree::insert(char *str) {
    FNode *node = readNode(root);
    cout << "WRITE TO " << tellp() << endl;
    addNode(node, root, str);
    seekp(0, ios::beg);
    peakCount++;
    cout << "PEAK " << tellp() << endl;
    write((char *) &peakCount, sizeof(int));
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
    insert(str);
    return *this;
}

Tree &Tree::operator<<(ifstream &is) {
    char buf[100];
    while (!is.eof()) {
        is >> buf;
        insert(buf);
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

long long Tree::createNode(char *str, size_t len) {
    seekp(0, ios::end);
    long long pos = tellp();
    FNode node(str, len);
    write((char *) &node.left, sizeof(long long));
    write((char *) &node.right, sizeof(long long));
    write((char *) &node.peakCount, sizeof(int));
    write((char *) &node.strLen, sizeof(size_t));
    write(node.str, MAXLEN * sizeof(char));
    return pos;
}

void Tree::copyNode(long long pos_node, char *str, int mode) {
//    FNode newNode(node->str, node->strLen);
    FNode *curNode = readNode(pos_node);
    if (curNode == nullptr) return;
    long long pos = createNode(curNode->str, curNode->strLen);

    // TODO delete old node
    long long newPos = createNode(str, strlen(str));
    seekp(pos_node);
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
        read((char *) &node->peakCount, sizeof(int));
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

long long Tree::findInd(long long pos, int *curInd, int needInd) {
    if (pos == FNULL) {
        return FNULL;
    }
    FNode *node = readNode(pos);
    if (*curInd == needInd && node->peakCount == 0) {
        return pos;
    }
    if (node->peakCount == 0) {
        (*curInd)++;
    }
    long long tmp = findInd(node->left, curInd, needInd);
    if (!tmp)
        tmp = findInd(node->right, curInd, needInd);
    return tmp;
}


FNode &Tree::operator[](int ind) {
    int tmp = 0;
    long long pos = findInd(root, &tmp, ind);
    FNode *node = readNode(pos);
    return *node;
}

int Tree::getSize() {
    return peakCount;
}

void Tree::editStr(int ind, const char *str, size_t len) {
    int tmp = 0;
    long long pos = findInd(root, &tmp, ind);
    seekp(pos + 2 * sizeof(long long) + sizeof(int));
    write((char *) &len, sizeof(size_t));
    write(str, len * sizeof(char));
    seekp(0, ios::end);
}

