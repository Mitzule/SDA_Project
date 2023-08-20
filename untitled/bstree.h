
#include<list>
#include <string>
#include <iostream>
#include <sstream>
#include <list>
using namespace std;

struct Node
{
    int key;       // key
    Node *p;     // pointer to parent
    Node *left;  // pointer to left child
    Node *right; // pointer to right child

    static Node* Nil;

    explicit Node(int k, Node *l = Nil, Node *r = Nil, Node *parent = Nil) :
            key(k), p(parent), left(l), right(r) { }

    string toString()
    {
        ostringstream os;
        os << key;
        return os.str();
    }

    ~Node()
    {
        if(left != Node::Nil)
            delete left;
        if(right != Node::Nil)
            delete right;
    }
};

Node* Node::Nil = new Node(0);

struct BSTree
{
    Node* root;

    BSTree()
    {
        root = Node::Nil;
    }

    ~BSTree()
    {
        delete root;
    }

    Node* createNode(int key)
    {
        return new Node(key);
    }

    Node* search(int k)
    {
        return search(root, k);
    }

    Node* search(Node* w, int key)
    {
        if (w == Node::Nil || w->key == key)
            return w;
        return search( (key < w->key) ? w->left : w->right, key);
    }

    Node* maximum(Node* w)
    {
        Node* x = w;
        while (x->right != Node::Nil)
            x = x->right;
        return x;
    }

    Node* minimum(Node* w)
    {
        Node* x = w;
        while (x->left != Node::Nil)
            x = x->left;
        return x;
    }

    Node* successor(Node* w)
    {
        Node* x = w;
        if (x->right != Node::Nil) return minimum(x->right);
        if (x->p == Node::Nil)
            return Node::Nil;
        Node* y = x->p;
        while (y != Node::Nil && x == y->right)
        {
            x = y;
            y = y->p;
        }
        return y;
    }

    Node* predecessor(Node* w)
    {
        Node* x = w;
        if (x->left != Node::Nil) return maximum(x->left);
        if (x->p == Node::Nil)
            return Node::Nil;
        Node* y = x->p;
        while (y != Node::Nil && x == y->left)
        {
            x = y;
            y = y->p;
        }
        return y;
    }

    void insert(Node* z)
    {
        Node *y = Node::Nil;
        Node *x = root;
        while (x != Node::Nil)
        {
            y = x;
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->p = y;
        if (y == Node::Nil)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }

    Node* del(Node* z)
    {
        Node *y = (z->left == Node::Nil || z->right == Node::Nil) ? z : successor(z);
        Node *x = (y->left != Node::Nil) ? y->left : y->right;
        x->p = y->p;
        if (y->p == Node::Nil)
        {
            root = x;
        }
        else
        {
            if (y == y->p->left)
                y->p->left = x;
            else
                y->p->right = z;
        }
        if (y != z)
        {
            z->key = y->key;
        }
        return y;
    }

    void inorder(Node* T)
    {
        if (T != Node::Nil)
        {
            inorder(T->left);
            cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        inorder(root);
    }

    void display(Node* w, int indent)
    {
        if (w != Node::Nil)
        {
            display(w->right, indent + 2);
            for (int i = 0; i < indent; i++) cout << ' ';
            cout << w->toString() << '\n';
            display(w->left, indent + 2);
        }
    }

    void indentedDisplay()
    {
        cout << "Arborele binar este: " <<endl;
        display(root, 0);
    }

    int depth()
    {
        return depth(root);
    }

    int depth(Node* n)
    {
        if (n == Node::Nil)
            return -1;
        int l = depth(n->left);
        int r = depth(n->right);
        return 1 + (l > r ? l : r);
    }
};

void startBSTreeProcessing(BSTree*);
void performBSTree(BSTree*, int);

namespace IODialogBSTree {
    void showBSTreeOperation() {
        cout << "1. Adauga nod" << endl
             << "2. Sterge nod" << endl
             << "3. Nod Minim" << endl
             << "4. Nod Maxim " << endl
             << "5. Succesorul Nodului" << endl
             << "6. Predecesorul Nodului " << endl
             << "7. Vizualizare Arbore" << endl
             << "8. Traversare Inorder" << endl
             << "9. Adancime Arbore" << endl
             << "10. Iesire" << endl
             << "Alege optiunea (1-10): ";
    }

    int getBSTreeOperation() {
        int option = 0;
        while (true) {
            showBSTreeOperation();
            if (!(cin >> option)) {
                cout << "Optiune necunoscuta, mai incearca" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else if (option < 1 || option > 10) {
                cout << "Optiune necunoscuta, mai incearca" << endl;
            } else {
                cout << "Optiune selectata: " << option << " .." << endl;
                cin.ignore(10000, '\n');
                break;
            }
        }
        return option;
    }

    void getBSNodeKeys(list<int> &nodeKeys) {
        cout << "Alege cheile nodului: " << flush;
        int key;
        string line;
        if (getline(cin, line)) {
            istringstream iss(line);
            while (iss >> key) {
                nodeKeys.push_back(key);
            }
        }
    }

    int getBSNodeKey() {
        cout << "Alege cheia nodului: ";
        int k;
        cin >> k;
        return k;
    }

    void performBSTree(BSTree* tree, int op)
    {
        list<int> nodeKeys;
        Node* nod;
        int skey;
        switch (op)
        {
            case 1:
                IODialogBSTree::getBSNodeKeys(nodeKeys);
                for (int & nodeKey : nodeKeys) {
                    tree->insert(tree->createNode(nodeKey));
                }
                break;
            case 2:
                skey = IODialogBSTree::getBSNodeKey();
                nod = tree->search(tree->root, skey);
                if (nod != nullptr) tree->del(nod);
                else cout << "Nod inexistent" << endl;
                break;
            case 3:
                nod = tree->minimum(tree->root);
                if (nod == nullptr ) cout << "Minim negasit" << endl;
                else cout << "Minimuml este: " << nod->toString() << endl;
                break;
            case 4:
                nod = tree->maximum(tree->root);
                if (nod == nullptr) cout << "Maxim negasit" << endl;
                else cout << "Maximul este: " << nod->toString() << endl;
                break;
            case 5:
                skey = IODialogBSTree::getBSNodeKey();
                nod = tree->search(tree->root, skey);
                if (nod != nullptr)
                {
                    nod = tree->successor(nod);
                    if (nod == nullptr)
                        cout << "Nodul cu cheia  " << skey << " nu are succesori.\n";
                    else cout << "Successorul este: " << nod->toString() << '\n';
                }
                else cout << "Nod negasit.\n";
                break;
            case 6:
                skey = IODialogBSTree::getBSNodeKey();
                nod = tree->search(tree->root, skey);
                if (nod != nullptr)
                {
                    nod = tree->predecessor(nod);
                    if (nod == nullptr) cout << "Nodul cu cheia " << skey << " nu are predecesor.\n";
                    else cout << "Predecesorul este: " << nod->toString() << '\n';
                }
                else cout << "Nod negasit.\n";
                break;
            case 7:
                tree->indentedDisplay();
                break;
            case 8:
                cout << "\nTraversarea Innorder este" << endl << ' ';
                tree->inorder();
                cout << endl;
                break;
            case 9:
                cout << "Adancimea arborelui este: " << tree->depth() << endl;
                break;
            case 10:
                delete tree;
                cout << "La revedere!" << endl;
                exit (0);
        }
    }

    void startBSTreeProcessing(BSTree* tree)
    {
        int op;
        while (true)
        {
            op = IODialogBSTree::getBSTreeOperation();
            IODialogBSTree::performBSTree(tree, op);
        }
    }
}

