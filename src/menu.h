//
// Created by 777 on 17.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_MENU_H
#define COURSEWORK_3_SEMESTER_MENU_H

#include <iostream>
#include "Tree.h"
#include <limits>
#include <csignal>

#define PATH "../data-sets/write.dat"

int inputFile(Tree &tree, int &count);

int outputFile(Tree &tree);

void addNewData(Tree &tree);

void printData(Tree &tree);

int clearData(Tree &tree, int &exit);

void editData(Tree &tree);

void deleteData(Tree &tree);

int menu();

void ignoreChars(int &status);

#endif //COURSEWORK_3_SEMESTER_MENU_H
