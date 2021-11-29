#pragma once
#include "Node.h"

class List {
    Node *first = nullptr;
    Node *last = nullptr;
    Node *front = nullptr;
    Node *back = nullptr;
    int sizeOfList = 0;
public:
    void addBeg(int key);
    void addEnd(int key);
    void delBeg();
    void delEnd();
    void printForward();
    void printBackward();
    void push(int key);
    void pop();
    void printQueue();
    void count();
    void garbageSoft();
    void garbageHard();
    void getSize() const;
    ~List();
};
