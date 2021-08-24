#include "Node.h"

class BTree {
    Node* root;
    int degree;
public:
    BTree();
    BTree(int degree);
    char search(int val);
    void printTree();
    void addVal(int val);
    void load(char input[]);
    void save();
    void clear(Node* node);
    ~BTree();
};


