#include <iostream>
#include "Tree.h"

int main() {
    Tree tree;
    char str1[] = "ABOBA1";
    char str2[] = "ABOBA2";
    char str3[] = "ABOBA3";
    char str4[] = "ABOBA4";
    char str5[] = "ABOBA5";
    char str6[] = "ABOBA6";
    char str7[] = "ABOBA7";
    char str8[] = "ABOBA8";
    char str9[] = "ABOBA9";
    tree.insert(str1);
    tree.insert(str2);
    tree.insert(str3);
    tree.insert(str4);
    tree.insert(str5);
    tree.insert(str6);
    tree.insert(str7);
    tree.insert(str8);
    tree.insert(str9);
    tree.printTree();
    Tree tr1;
    tr1.insert(str1);
    ofstream out("write.dat", ios::out | ios::binary);
    if (!out) {
        cout << "Cannot open file!" << endl;
        return 1;
    }
    out << tr1;
    out.close();

    ifstream in("write.dat", ios::out | ios::binary);
    if (!in) {
        cout << "Cannot open file!" << endl;
        return 1;
    }
    Tree tr2;
    in >> tr2;
    in.close();

    return 0;
}
