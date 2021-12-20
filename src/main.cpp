#include "menu.h"
#include <iostream>
#include "Tree.h"

using namespace std;

void read(fstream &fs) {
    char buf[100];
    size_t n;
    FNode fn;
    long long ptr1;
    long long ptr2;
    int m;
    fs.read((char *) &ptr1, sizeof(long long));
    fs.read((char *) &ptr2, sizeof(long long));
    fs.read((char *) &m, sizeof(m));
    fs.read((char *) &n, sizeof(size_t));
    fs.read(buf, n * sizeof(char));
    buf[n] = '\0';
    if (m == 0)cout << ptr1 << ' ' << ptr2 << ' ' << n << ' ' << buf << ' ' << fs.tellp() << endl;
}

int main() {
//    menu();
    char name[] = "../data-sets/test.dat";
    Tree tr1(name);
    char str1[] = "ABOBA1";
    char str2[] = "ABOBA2";
    char str3[] = "ABOBA3";
    char str4[] = "ABOBA4";
    char str5[] = "ABOBA5";
    char str6[] = "ABOBA6";
    char str7[] = "ABOBA7";
    char str8[] = "ABOBA8";
    char str9[] = "ABOBA9";
    tr1.insert(str1);
    tr1.insert(str2);
    tr1.insert(str3);
    tr1.insert(str4);
    tr1.insert(str5);
    tr1.insert(str6);
    tr1.insert(str7);
    tr1.insert(str8);
    tr1.insert(str9);
    cout << tr1;
//    cout << tr1.fail();
    tr1.close();
//    fstream fs(name, ios::in | ios::binary);
//    if (!fs.is_open())return -2;
//    fs.seekp(0, ios::end);
//    long long pos = fs.tellg();
//    fs.seekp(0, ios::beg);
//    for (int i = 0; i < pos / 34; ++i) {
//        read(fs);
//    }
//    fs.close();
    return 0;
}

