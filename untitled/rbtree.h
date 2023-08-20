
#include<list>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

struct RBNode
{
    int key;       // key
    RBNode *p;     // pointer to parent
    RBNode *left;  // pointer to left child
    RBNode *right; // pointer to right child
    enum color { RED, BLACK };
    color col;

    static RBNode* Nil;

    explicit RBNode(int k, RBNode *l = Nil, RBNode *r = Nil, RBNode *parent = Nil, color c = RBNode::BLACK) :
            key(k), p(parent), left(l), right(r), col(c) { }

    string toString() const
    {
        ostringstream os;
        os << key << ((col == RBNode::RED) ? ":r" : ":b");
        return os.str();
    }

    ~RBNode()
    {
        if (this != Nil)
        {
            if(left != Nil)
                delete left;
            if(right != Nil)
                delete right;
        }
    }

};

RBNode* RBNode::Nil = new RBNode(0);

struct RBTree
{
    RBNode* root;

    void LeftRotate(RBNode* x)
    {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != RBNode::Nil)
            y->left->p = x;
        y->p = x->p;
        if (x->p == RBNode::Nil)
            root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
        y->left = x;
        x->p = y;
    }

    void RightRotate(RBNode* y)
    {
        RBNode* x = y->left;
        y->left = x->right;
        if (x->right != RBNode::Nil)
            x->right->p = y;
        x->p = y->p;
        if (y->p == RBNode::Nil)
            root = x;
        else if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
        x->right = y;
        y->p = x;
    }

    RBTree()
    {
        root = RBNode::Nil;
    }
    ~RBTree()
    {
        delete root;
    }

    static RBNode* createNode(int key)
    {
        return new RBNode(key);
    }

    static bool isNil(RBNode* n)
    {
        return (n == RBNode::Nil);
    }

    RBNode* search(RBNode* w, int key)
    {
        if (isNil(w) || w->key == key)
            return w;
        return search((key < w->key) ? w->left : w->right, key);
    }

    static RBNode* maximum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->right))
            x = x->right;
        return x;
    }

    static RBNode* minimum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->left))
            x = x->left;
        return x;
    }

    RBNode* successor(RBNode* w)
    {
        if (isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->right))
            return minimum(x->right);
        RBNode* y = x->p;
        while (!isNil(y) && x == y->right)
        {
            x = y;
            y = x->p;
        }
        return y;
    }

    static RBNode* predecessor(RBNode* w)
    {
        if (isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->left))
            return maximum(x->left);
        RBNode* y = x->p;
        while (!isNil(y) && x == y->left)
        {
            x = y;
            y = x->p;
        }
        return y;
    }

    void RBInsert(RBNode* z)
    {
        RBNode* y = RBNode::Nil;
        RBNode* x = root;
        while (!isNil(x))
        {
            y = x;
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->p = y;
        if (isNil(y))
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->left = z->right = RBNode::Nil;
        z->col = RBNode::RED;
        RBInsertFixup(z);
    }

    RBNode* del(RBNode* z)
    {
        RBNode* y = (isNil(z->left) || isNil(z->right)) ? z : successor(z);
        RBNode* x = !isNil(y->left) ? y->left : y->right;
        x->p = y->p;
        if (isNil(y->p))
        {
            root = x;
        }
        else
        {
            if (y == y->p->left)
                y->p->left = x;
            else
                y->p->right = x;
        }
        if (y != z)
        {
            z->key = y->key;
        }
        if (y->col == RBNode::BLACK)
            RBDeleteFixup(x);
        return y;
    }

    void RBDeleteFixup(RBNode* x)
    {
        RBNode* w;
        while ((x != root) && (x->col == RBNode::BLACK))
        {
            if (x == x->p->left)
            {
                w = x->p->right;
                if (w->col == RBNode::RED)
                {
                    w->col = RBNode::BLACK;
                    x->p->col = RBNode::RED;
                    LeftRotate(x->p);
                    w = x->p->right;
                }
                if ((w->left->col == RBNode::BLACK) && (w->right->col == RBNode::BLACK))
                {
                    w->col = RBNode::RED;
                    x = x->p;
                }
                else
                {
                    if (w->right->col == RBNode::BLACK)
                    {
                        w->left->col = RBNode::BLACK;
                        w->col = RBNode::RED;
                        RightRotate(w);
                        w = x->p->right;
                    }
                    w->col = x->p->col;
                    x->p->col = RBNode::BLACK;
                    w->right->col = RBNode::BLACK;
                    LeftRotate(x->p);
                    x = root;
                }
            }
            else
            {
                w = x->p->left;
                if (w->col == RBNode::RED)
                {
                    w->col = RBNode::BLACK;
                    x->p->col = RBNode::RED;
                    RightRotate(x->p);
                    w = x->p->left;
                }
                if ((w->left->col == RBNode::BLACK) && (w->right->col == RBNode::BLACK))
                {
                    w->col = RBNode::RED;
                    x = x->p;
                }
                else
                {
                    if (w->left->col == RBNode::BLACK)
                    {
                        w->right->col = RBNode::BLACK;
                        w->col = RBNode::RED;
                        LeftRotate(w);
                        w = x->p->left;
                    }
                    w->col = x->p->col;
                    x->p->col = RBNode::BLACK;
                    w->left->col = RBNode::BLACK;
                    RightRotate(x->p);
                    x = root;
                }
            }
        }
        x->col = RBNode::BLACK;
    }

    void RBInsertFixup(RBNode* z)
    {
        while (z->p->col == RBNode::RED)
            if (z->p == z->p->p->left)
            {
                RBNode* y = z->p->p->right;
                if (y->col == RBNode::RED)
                {
                    z->p->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                }
                else
                {
                    if (z == z->p->right)
                    {
                        z = z->p;
                        LeftRotate(z);
                    }
                    z->p->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                    RightRotate(z->p->p);
                }
            }
            else
            {
                RBNode* y = z->p->p->left;
                if (y->col == RBNode::RED)
                {
                    z->p->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                }
                else
                {
                    if (z == z->p->left)
                    {
                        z = z->p;
                        RightRotate(z);
                    }
                    z->p->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                    LeftRotate(z->p->p);
                }
            }
        root->col = RBNode::BLACK;
    }

    void inorder(RBNode* T)
    {
        if (!isNil(T))
        {
            inorder(T->left);
            cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        if (isNil(root))
        {
            cout << "Gol";
        }
        else
            inorder(root);
    }

    void display(RBNode* w, int indent)
    {
        if (!isNil(w))
        {
            display(w->right, indent + 2);
            for (int i = 0; i < indent; i++) cout << ' ';
            cout << w->toString() << '\n';
            display(w->left, indent + 2);
        }
    }

    void indentedDisplay()
    {
        if (isNil(root))
            cout << "Arborele RB este gol: " << endl;
        else
        {
            cout << "Arborele RB este: " << endl;
            display(root, 0);
        }
    }

    int bh(RBNode* w)
    {
        if (isNil(w))
            return 0;
        else
            return bh(w->left) + (w->col == RBNode::BLACK ? 1 : 0);
    }

//    int bh(RBNode* w)
//    {
//        if (isNil(w))
//            return 0;
//        else
//        {
//            int l = bh(w->left);
//            int r = bh(w->right);
//            if (l == r)
//                return l + (w->col == RBNode::BLACK ? 1 : 0);
//            else
//                return -1;
//        }
//    }

    static int countBlacks(RBNode* x)
    {
        int count = 0;
        while (!isNil(x))
        {
            if (x->col == RBNode::BLACK)
                count++;
            x = x->left;
        }
        return count;
    }

    int blackHeight()
    {
        return bh(root);
    }

    int depth(RBNode* x)
    {
        if (isNil(x))
        {
            return -1;
        }
        else
        {
            int lDepth = depth(x->left);
            int rDepth = depth(x->right);
            return (lDepth < rDepth ? rDepth : lDepth) + 1;
        }
    }

    int depth()
    {
        return depth(root);
    }

    int maxBlackKey()
    {
        RBNode* x = root;
        int max = -1000;
        while (!isNil(x))
        {
            if (x->col == RBNode::BLACK){
                if (x->key > max)
                    max = x->key;
            }
            x = x->right;
        }
        return max;
    }

    int maxRedKey()
    {
        RBNode* x = root;
        int max = 0;
        while (!isNil(x))
        {
            if (x->col == RBNode::RED){
                if (x->key > max)
                    max = x->key;
            }
            x = x->right;
        }
        return max;
    }
};

void performRB(RBTree*, int);
void startRBTreeProcessing(RBTree*);

namespace IODialogRBTree
{
    void showRBTreeOperation()
    {
        cout << "1. Add noduri" << endl
             << "2. Sterge noduri" << endl
             << "3. Nod minim" << endl
             << "4. Nod maxim" << endl
             << "5. Succesorul nodului" << endl
             << "6. Predecesorul nodului" << endl
             << "7. Afisare arbore" << endl
             << "8. Parcurgere Inorder" << endl
             << "9. Inaltimea black" << endl
             << "10. Cheia maxima nod negru" << endl
             << "11. Cheia maxima nod rosu" << endl
             << "12. Adancimea arbore" << endl
             << "13. Iesire" << endl
             << "Alege optiunea (1-13): ";
    }

    int getRBTreeOperation()
    {
        int option = 0;
        while (true)
        {
            showRBTreeOperation();
            if (!(cin >> option))
            {
                cout << "Optiune necunoscuta, mai incearca!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else if (option < 1 || option > 13)
            {
                cout << "Optiune necunoscuta, mai incearca!" << endl;
            }
            else
            {
                cout << "Optiune selectata: " << option << " .." << endl;
                cin.ignore(10000, '\n');
                break;
            }
        }
        return option;
    }

    void getRBNodeKeys(list<int>& nodeKeys)
    {
        cout << "Alege valoarea nodurilor: " << flush;
        int key;
        string line;
        if (getline(cin, line))
        {
            istringstream iss(line);
            while (iss >> key)
            {
                nodeKeys.push_back(key);
            }
        }
    }

    int getRBNodeKey()
    {
        cout << "Alege valoarea nodului: ";
        int k;
        cin >> k;
        return k;
    }

    void performRB(RBTree* RB, int o)
    {
        list<int> nodeKeys;
        RBNode* rbn;
        int skey;
        switch (o)
        {
            case 1:
                IODialogRBTree::getRBNodeKeys(nodeKeys);
                for (int & nodeKey : nodeKeys) {
                    RB->RBInsert(RBTree::createNode(nodeKey));
                }
                break;
            case 2:
                skey = IODialogRBTree::getRBNodeKey();
                rbn = RB->search(RB->root, skey);
                if (!RBTree::isNil(rbn)) RB->del(rbn);
                else cout << "RB: Negasit" << endl;
                break;
            case 3:
                rbn = RBTree::minimum(RB->root);
                if (RBTree::isNil(rbn) ) cout << "RB: Minim negasit" << endl;
                else cout << "RB: Minimul este: " << rbn->toString() << endl;
                break;
            case 4:
                rbn = RBTree::maximum(RB->root);
                if (RBTree::isNil(rbn) ) cout << "RB: Maxim negasit" << endl;
                else cout << "RB: Maximul este: " << rbn->toString() << endl;
                break;
            case 5:
                skey = IODialogRBTree::getRBNodeKey();
                rbn = RB->search(RB->root, skey);
                if (!RBTree::isNil(rbn))
                {
                    rbn = RB->successor(rbn);
                    if (RBTree::isNil(rbn))
                        cout << "RB: Nodul nu are succesor.\n";
                    else cout << "RB: Succesorul este: " << rbn->toString() << '\n';
                }
                else cout << "RB: Nod negasit.\n";
                break;
            case 6:
                skey = IODialogRBTree::getRBNodeKey();
                rbn = RB->search(RB->root, skey);
                if (!RBTree::isNil(rbn))
                {
                    rbn = RBTree::predecessor(rbn);
                    if (RBTree::isNil(rbn)) cout << "RB: Nodul nu are predecesor.\n";
                    else cout << "RB: Predecesorul este: " << rbn->toString() << '\n';
                }
                else cout << "RB: Nod negasit.\n";
                break;
            case 7: // Show tree RB
                RB->indentedDisplay();
                break;
            case 8:
                cout << "\nParcurgere Inorder al arborelui RB:" << endl << ' ';
                RB->inorder();
                cout << endl;
                break;
            case 9:
                cout << "Inaltimea black al arborelui RB tree este " << RB->blackHeight() << endl;
                break;
            case 10:
                cout << "Cheia maxima nod negru al arborelui RB tree este " << RB->maxBlackKey() << endl;
                break;
            case 11:
                cout << "Cheia maxima nod rosu al arborelui RB tree este " << RB->maxRedKey() << endl;
                break;
            case 12:
                cout << "Adancimea arbore RB este " << RB->depth() << endl;
                break;
            case 13:
                delete RB;
                cout << "La revedere!" << endl;
                exit (0);
        }

    }

    void startRBTreeProcessing(RBTree* RB)
    {
        int o;
        while (true)
        {
            o = IODialogRBTree::getRBTreeOperation();
            IODialogRBTree::performRB(RB, o);
        }
    }

}
