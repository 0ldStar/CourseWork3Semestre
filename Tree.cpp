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


Tree::Tree(Tree &a) {
    root = nullptr; // TODO
    level = a.level;
    peakCount = a.peakCount;
}

void Tree::insert(char *str) {
    addNode(&root, str);
    peakCount++;
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
//        cout << buf << '|' << endl;
        addNode(&root, buf);
        peakCount++;
    }
    return *this;
}

//Tree &Tree::operator>>(ostream &os) {
//    printNode(root, os);
//    return *this;
//}

long long Tree::PutTree(Node *q) {
    if (q == nullptr) return FNULL;
    FNode CUR;
    CUR.m = q->m; // Текущая вершина - локальная переменная
    long long pos;
    CUR.left = PutTree(q->left);
    CUR.right = PutTree(q->right);
    pos = tellp();                            // Адрес вершины
    CUR.strLen = q->strLen;            // Длина строки (ЗПД)
    write((char *) &CUR, sizeof(FNode));                // Сохранить вершину
    write(q->str, CUR.strLen * sizeof(char));           // Сохранить строку
    return pos;
}


void Tree::toBinary() {
    long long pos0;
    write((char *) &pos0, sizeof(long));     // Резервировать место под указатель
    pos0 = PutTree(root);                  // Сохранить дерево
    seekp(ios_base::beg);
    write((char *) &pos0, sizeof(long));
}

Node *Tree::GetTree(long long pos) {           // Вход - адрес вершины в файле
    if (pos == FNULL) return nullptr;  // Результат - указатель на
    Node *q = new Node;                       // вершину поддерева в памяти
    FNode A;// Текущая вершина из файла -
    seekp(pos);
    read((char *) &A, sizeof(FNode));
    q->strLen = A.strLen;
    if (q->strLen == 0) {
        q->str = nullptr;
    } else {
        q->str = new char[A.strLen];               // Загрузка строки - ЗПД
        read((char *) q->str, A.strLen);
        peakCount++;
    }
    q->m = A.m;
    q->left = GetTree(A.left);
    q->right = GetTree(A.right);

    return q;
}

void Tree::LoadTree() {
    long long phead;
    read((char *) &phead, sizeof(long));
    this->root = GetTree(phead);
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

//void Tree::printTree() {
//    printNode(root);
//}


