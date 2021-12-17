//
// Created by 777 on 17.12.2021.
//
#include <iostream>
#include "Tree.h"
#include "menu.h"

// in the end if changed data base, do you want save changes
// do you want view text entry
// report how many data was read from binary
// error data base is not open
int menu() {
    int error = 0, menu_pos = -1, exit = 0;
    Tree tree;
    tree.open("../data-sets/write.dat", ios::in | ios::out | ios::binary);
    if (tree.is_open()) {
        tree.LoadTree();
        while (!exit) {
            cout << "Choose the option\n";
            cout << "# 0 Exit\n";
            cout << "# 1 Read data from txt\n";
            cout << "# 2 Write data in txt\n";
            cout << "# 3 Add new data to base\n";
            cout << "# 4 Print data to Terminal\n";
            cout << "# 5 Edit data\n";
            cout << "# 6 Delete data\n";
            cout << "# 7 Clear data base\n";
            cin >> menu_pos;
            if (menu_pos >= 0 && menu_pos <= 7) {
                switch (menu_pos) {
                    case 0: {
                        exit = 1;
                        break;
                    }
                    case 1: {
                        error = inputFile(tree); // how much writes read;
                        break;
                    }
                    case 2: {
                        error = outputFile(tree);
                        break;
                    }
                    case 3: {
                        error = addNewData(tree);
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
        for (int i = 0; i < tree[0].strLen; ++i) {
            cout << tree[0].str[i];
        }
        tree.toBinary();
        tree.close();
    } else {
        error = -1;
    }

    return error;
}

int inputFile(Tree &tree) {
    int error = 0;
    string name;
    cout << "Enter path to file: ";
    cin >> name;
    ifstream is(name, ios::in);
    if (is.is_open()) {
        tree << is;
    } else {
        cout << "Can`t open file!\n";
        error = 1;
    }
    is.close();
    return error;
}

int outputFile(Tree &tree) {
    int error = 0;
    string name;
    cout << "Enter path to file: ";
    cin >> name;
    ofstream os(name, ios::out);
    if (os.is_open()) {
        os << tree;
    } else {
        cout << "Can`t open file!";
        error = 1;
    }
    os.close();
    return error;
}

int addNewData(Tree &tree) {
    int error = 0;
    string str;
    cout << "Enter string:";
    cin >> str;
    tree.insert((char *) str.c_str());
    cout << "Do you want to save changes to text file ? (1-Yes/2-No)";
    int choose;
    while (true) {
        cin >> choose;
        if (choose != 1 && choose != 2) {
            cout << "Incorrect number";
            cout << "Do you want to save changes to text file ? (1-Yes/2-No)";
        } else {
            if (choose == 1) {
                error = outputFile(tree);
            }
            break;
        }

    }
    return error;
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
                    if (index >= 0 && index < tree.getSize()) {
                        Node node = tree[index];
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
    cout << "Warning!!!\n Are you really want to delete all data from base? (1-Yes/2-No)";
    int choose;
    while (true) {
        cin >> choose;
        if (choose != 1 && choose != 2) {
            cout << "Incorrect number";
            cout << "Warning!!!\n Are you really want to delete all data from base? (1-Yes/2-No)";
        } else {
            if (choose == 1) {
                tree.free();
                cout << "Yeap";
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
        if (index >= 0 && index < tree.getSize()) {
            for (int i = 0; i < tree[index].strLen; ++i)
                cout << tree[index].str[i];
            cout << endl;
            string str;
            cout << "Enter string: ";
            cin >> str;
            tree[index].str = (char *) str.c_str();
            tree[index].strLen = str.length();
            break;
        } else {
            cout << "Incorrect index";
            cout << "Current tree have " << tree.getSize() << " elements\n";
            cout << "You can choose one of them [0-" << tree.getSize() - 1
                 << "] for edit\nEnter index: ";
        }
    }
}

void deleteData(Tree &tree) {
    cout << "Current tree have " << tree.getSize() << " elements\n";
    cout << "You can choose one of them [0-" << tree.getSize() - 1 << "] for delete\nEnter index: ";
    int index;
    while (true) {
        cin >> index;
        if (index >= 0 && index < tree.getSize()) {
            for (int i = 0; i < tree[index].strLen; ++i)
                cout << tree[index].str[i];
            cout << endl;
            Node *node = &tree[index];
            free(node->str);
            node->str = nullptr;
            node->strLen = 0;
            break;
        } else {
            cout << "Incorrect index";
            cout << "Current tree have " << tree.getSize() << " elements\n";
            cout << "You can choose one of them [0-" << tree.getSize() - 1
                 << "] for delete\nEnter index: ";
        }
    }
}
