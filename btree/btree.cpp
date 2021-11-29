#include "BTree.h"
#include <iostream>
#define INPUT 5000


BTree::BTree()
{
    this->root = nullptr;
    this->degree = 0;
}

BTree::BTree(int degree)
{
    this->root = nullptr;
    this->degree = degree;
}

void BTree::printTree()
{
    if (this->root)
        this->root->print();
}

void BTree::addVal(int val)
{
    if (this->root) //istnieje juz drzewo
    {
        if (root->currNum == 2*degree-1) //korzen jest pelny
        {
            Node* temp = new Node(degree, false); //alokuje pamiec dla nowego korzenia
            temp->childPtr[0] = this->root; //stary korzen jest dzieckiem nowego korzenia
            temp->split(0, this->root); //splituje stary korzen

            int index = 0;
            if (temp->keys[0] < val) //ktore dziecko bedzie mialo klucz
                ++index;
            temp->childPtr[index]->insertToTree(val);

            this->root = temp; //zamiana korzenia
        }
        else
        {
            this->root->insertToTree(val); //jezeli korzen nie jest pelny to po prostu dodaje
        }
    }
    else //drzewo jest puste
    {
        this->root = new Node(this->degree, true);
        this->root->keys[0] = val;
        this->root->currNum = 1;
    }
}

char BTree::search(int val) {
    if (this->root)
    {
        Node* temp = this->root->search(val);
        if (!temp)
            return '-';
        return '+';
    }
    return '-';
}

void BTree::load(char *input)
{
    int i = 1;
    this->root = new Node(this->degree, true);
    this->root->loadToTree(input, i);
}

void BTree::save()
{
    if (this->root)
        printf("%d\n", this->degree);
    this->root->saveTree();
}

void BTree::clear(Node *node)
{
    for (int i = 0; i < node->currNum; i++)
    {
        if (node->childPtr[i])
        {
            clear(node->childPtr[i]);
            delete node->childPtr[i];
            node->childPtr[i] = nullptr;
        }
    }
}

BTree::~BTree()
{
    if(this->root)
    {
        clear(this->root);
    }
}