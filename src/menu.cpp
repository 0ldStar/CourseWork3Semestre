//
// Created by 777 on 17.12.2021.
//
#include "menu.h"

// Сжатие если m=0 и len = 0
int menu() {
    int error, menuPos, exit, newDataCount;
    Tree tree(PATH);
    string buf;
//    signal(SIGINT, SIG_IGN);
//    signal(SIGBREAK, SIG_IGN);
    error = 0;
    menuPos = -1;
    exit = 0;
    newDataCount = 0;
    if (tree.is_open()) {
        cout << "      Was read " << tree.getSize() << " strings from data base\n";

        while (!exit) {
            cout << "############################################\n";
            cout << "#           Choose the option              #\n";
            cout << "#  1 Read data from txt                    #\n";
            cout << "#  2 Write data in txt                     #\n";
            cout << "#  3 Add new data to base from Terminal    #\n";
            cout << "#  4 Print data to Terminal                #\n";
            cout << "#  5 Edit data                             #\n";
            cout << "#  6 Delete data                           #\n";
            cout << "#  7 Clear data base                       #\n";
            cout << "#  0 Exit                                  #\n";
            cout << "############################################\n";
            cin >> menuPos;
            ignoreChars(menuPos);
            if (menuPos >= 0 && menuPos <= 7) {
                switch (menuPos) {
                    case 0: {
                        exit = 1;
                        break;
                    }
                    case 1: {
                        error = inputFile(tree, newDataCount);
                        break;
                    }
                    case 2: {
                        error = outputFile(tree);
                        break;
                    }
                    case 3: {
                        addNewData(tree);
                        newDataCount++;
                        break;
                    }
                    case 4: {
                        printData(tree);
                        break;
                    }
                    case 5: {
                        editData(tree);
                        break;
                    }
                    case 6: {
                        deleteData(tree);
                        break;
                    }
                    case 7: {
                        error = clearData(tree, exit);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        tree.close();
    } else {
        cerr << "Data base read error!!!";
        error = -1;
    }

    return error;
}

int inputFile(Tree &tree, int &count) {
    int error = 0;
    string name;
    int b_size = tree.getSize();
    cout << "Enter path to file: ";
    cin >> name;
    ifstream is(name, ios::in);
    if (is.is_open()) {
        tree << is;
        cout << "Was read " << tree.getSize() - b_size << " strings\n";
        count += tree.getSize() - b_size;
    } else {
        cerr << "Can`t open file!\n";
        error = 1;
    }
    is.close();
    return error;
}

int outputFile(Tree &tree) {
    if (tree.getSize() == 0) {
        cout << "Tree is empty\n";
        return 0;
    }
    int error = 0;
    string name;
    cout << "Enter path to file: ";
    cin >> name;
    ofstream os(name, ios::out | ios::app);
    if (os.is_open()) {
        os << tree;
        cout << "Was wrote " << tree.getSize() << " elements\n";
    } else {
        cout << "Can`t open file!";
        error = 1;
    }
    os.close();
    return error;
}

void addNewData(Tree &tree) {
    string str;
    cout << "Enter string:";
    cin >> str;
    tree.insert((char *) str.c_str());
}

void printData(Tree &tree) {
    if (tree.getSize() == 0) {
        cout << "Tree is empty\n";
        return;
    }
    cout << "Print all tree or element from index? (1/2)";
    int choose;
    while (true) {
        cin >> choose;
        ignoreChars(choose);
        if (choose != 1 && choose != 2) {
            cout << "Incorrect number";
            cout << "Print all tree or element from index? (1/2)";
        } else {
            if (choose == 1) {
                cout << tree << endl;
            } else if (choose == 2) {

                cout << "Current tree have " << tree.getSize() << " elements\n";
                cout << "You can choose one of them [0-" << tree.getSize() - 1 << "]\nEnter index: ";
                int index;
                while (true) {
                    cin >> index;
                    ignoreChars(index);
                    if (index >= 0 && index < tree.getSize()) {
                        FNode node = tree[index];
                        for (int i = 0; i < node.strLen; ++i) {
                            cout << node.str[i];
                        }
                        cout << endl;
                        break;
                    } else {
                        cout << "Incorrect index";
                        cout << "Current tree have " << tree.getSize() << " elements\n";
                        cout << "You can choose one of them [0-" << tree.getSize() - 1
                             << "]\nEnter index: ";
                    }

                }
            }
            break;
        }

    }

}

int clearData(Tree &tree, int &exit) {
    int error = 0;
    cout << "Warning!!!\n Are you really want to delete all data from base? (1-Yes/0-No)";
    int choose;
    while (true) {
        cin >> choose;
        ignoreChars(choose);
        if (choose != 1 && choose != 0) {
            cout << "Incorrect number!\n";
            cout << "Warning!!!\n Are you really want to delete all data from base? (1-Yes/0-No)";
        } else {
            if (choose == 1) {
//                cout << "Yeap";
                tree.close();
                tree.update();
                tree.open("../data-sets/write.dat", ios::in | ios::out | ios::binary | ios::trunc);
                if (!tree.is_open()) {
                    error = -1;
                    exit = 1;
                }
                //tree.LoadTree();
            }
            break;
        }

    }
    return error;
}

void editData(Tree &tree) {
    if (tree.getSize() == 0) {
        cout << "Tree is empty\n";
        return;
    }
    cout << "Current tree have " << tree.getSize() << " elements\n";
    cout << "You can choose one of them [0-" << tree.getSize() - 1 << "] for edit\nEnter index: ";
    int index;
    while (true) {
        cin >> index;
        ignoreChars(index);
        if (index >= 0 && index < tree.getSize()) {
            for (int i = 0; i < tree[index].strLen; ++i)
                cout << tree[index].str[i];
            cout << endl;
            string str;
            cout << "Enter string: ";
            cin >> str;
            if (str.length() > MAXLEN) {
                cout << "Sorry, length is too long. Enter a string less than " << MAXLEN << " in length\n";
            } else {
                tree.editStr(index, str.c_str(), str.length());
            }
            break;
        } else {
            cout << "Incorrect index!\n";
            cout << "Current tree have " << tree.getSize() << " elements\n";
            cout << "You can choose one of them [0-" << tree.getSize() - 1
                 << "] for edit\nEnter index: ";
        }
    }
}

void deleteData(Tree &tree) {
    cout << "Current tree have " << tree.getSize() << " elements\n";
    cout << "You can choose one of them [0-" << tree.getSize() - 1 << "] for delete\nEnter index: ";
    int index, choose;
    while (true) {
        cin >> index;
        ignoreChars(index);
        if (index >= 0 && index < tree.getSize()) {
            FNode node = tree[index];
            for (int i = 0; i < node.strLen; ++i)
                cout << node.str[i];
            cout << endl;
            cout << "Are you sure delete this element? (1-Yes/0-No)";
            while (true) {
                cin >> choose;
                ignoreChars(choose);
                if (choose != 1 && choose != 0) {
                    cout << "Incorrect number!\n";
                    cout << "Are you sure delete this element? (1-Yes/0-No)";
                } else {
                    if (choose == 1) {
                        char tmp;
                        tree.editStr(index, &tmp, 0);
                    }
                    break;
                }

            }
            break;
        } else {
            cout << "Incorrect index!\n";
            cout << "Current tree have " << tree.getSize() << " elements\n";
            cout << "You can choose one of them [0-" << tree.getSize() - 1
                 << "] for delete\nEnter index: ";
        }
    }
}


void ignoreChars(int &status) {
    if (cin.fail()) status = -1;
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}