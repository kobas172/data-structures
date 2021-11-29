#pragma once
#include "Node.h"

class List {
    Node* actual = nullptr;
    Node* prev = nullptr;
    Node* first = nullptr;
    Node* last = nullptr;
public:
    void addBeg (int data);
    void addEnd (int data);
    void addActual (int data);
    void printForward();
    void printBackward();
    void printActual() const;
    void printNext();
    void printPrevious();
    void deleteBeg();
    void deleteEnd();
    void deleteActual();
    void deleteValue(int data);
    Node *XOR (Node* left, Node* right);
    ~List();
};
