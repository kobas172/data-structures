#include <iostream>
#include "BTree.h"
#define INPUT 5000

int main()
{
    char cmd, load[INPUT];
    int key;
    BTree tree;

    while (scanf("%s", &cmd) > 0)
    {
        if (cmd == 'I')
        {
            scanf("%d", &key);
            tree = BTree(key);
        }
        else if (cmd == 'A')
        {
            scanf("%d", &key);
            tree.addVal(key);
        }
        else if (cmd == 'P')
        {
            tree.printTree();
        }
        else if (cmd == '?')
        {
            scanf("%d", &key);
            cmd = tree.search(key);
            std::cout << key << " " << cmd << std::endl;
        }
        else if (cmd == 'L')
        {
            scanf("%d", &key);
            tree = BTree(key);
            std::cin.ignore();
            std::cin.getline(load, INPUT);
            tree.load(load);
        }
        else if (cmd == 'S')
        {
            tree.save();
        }
        else if (cmd == 'X')
        {
            exit(1);
        }
    }
}
