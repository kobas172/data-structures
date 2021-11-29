#pragma once

class Node {
    int data;
    Node* node;
public:
    Node();
    Node (int data, Node* node);
    void setNode(Node* node);
    Node* getNode() const;
    int getData() const;
};
