#include <iostream>

#include "rbtree.h"
#include "bstree.h"

void afisareTreeOp();
int getTreeOp();

int main() {
    auto *RB = new RBTree();
    auto *BST = new BSTree();
    int x = 0, choice = 0;
    do {
        afisareTreeOp();
        cout << "Alege Optiunea: ";
        cin >> choice;
        switch (choice) {
            case 1:
                IODialogBSTree::startBSTreeProcessing(BST);
                break;
            case 2:
                IODialogRBTree::startRBTreeProcessing(RB);
                break;
            default:
                cout << "Nu exista optiunea aceasta";
                break;
            case 4:
                cout << "La revedere!";
                exit(0);
        }
    } while (true);
}

void afisareTreeOp(){
    cout << "1. Binary Search Tree" << endl
         << "2. Red-Black Tree" << endl
         << "3. Iesire" << endl;
}