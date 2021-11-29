#pragma once

class Node {
    int key;
    Node* link;
public:
    Node();
    Node (int key, Node* link);
    void setLink(Node* link);
    void setKey(int key);
    Node* getLink() const;
    int getKey() const;
};