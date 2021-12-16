#include <iostream>
#include "Tree.h"
#include <fstream>

int menu();

int main() {
//    Tree tree;
//    tree.open("../write.dat", ios::out | ios::binary);
//    if (tree.is_open()) {
//        char str1[] = "ABOBA1";
//        char str2[] = "ABOBA2";
//        char str3[] = "ABOBA3";
//        char str4[] = "ABOBA4";
//        char str5[] = "ABOBA5";
//        char str6[] = "ABOBA6";
//        char str7[] = "ABOBA7";
//        char str8[] = "ABOBA8";
//        char str9[] = "ABOBA9";
//        tree << str1;
//        tree << str2;
//        tree << str3;
//        tree << str4;
//        tree << str5;
//        tree << str6;
//        tree << str7;
//        tree << str8;
//        tree << str9;
//        cout << tree;
//        tree.toBinary();
//    }
//    ofstream os("../write.txt", ios::out);
//    if (os.is_open()) {
//        os << tree;
//    }
//    os.close();
//    tree.close();
//    cout << endl;
//    Tree tr;
//    tr.open("../write.dat", ios::in | ios::binary);
//    if (tr.is_open()) {
//        ifstream is("../read.txt", ios::in);
//        if (is.is_open()) {
//            tr << is;
//            cout << tr;
//        }
//        is.close();
//    }
//    tr.close();
    menu();
    return 0;
}

int menu() {
    int error = 0, menu_pos;
    Tree tree;
    cout << "Choose the option\n";
    cout << "# 1 Read data from txt\n";
    cout << "# 2 Write data in txt\n";
    cin >> menu_pos;
    switch (menu_pos) {
        case 1: {
            string name;
            cout << "Enter path to file: ";
            cin >> name;
            ifstream is(name, ios::in);
            if (is.is_open()) {
                tree << is;
            } else {
                error = 1;
            }
            is.close();
            break;
        }
        case 2: {
            string name;
            cout << "Enter path to file: ";
            cin >> name;
            ofstream os(name, ios::out);
            if (os.is_open()) {
                os << tree;
            } else {
                error = 1;
            }
            os.close();
            break;
        }
        default:
            break;
    }
    cout << '\n' << tree;
    return error;
}
