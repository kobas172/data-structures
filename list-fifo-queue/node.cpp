#include "Node.h"

Node::Node() {
    this->key=0;
    this->link=nullptr;
}

Node::Node(int key, Node *link) {
    this->key = key;
    this->link = link;
}

void Node::setKey(int key) {
    this->key = key;
}

void Node::setLink(Node *link) {
    this->link = link;
}

Node *Node::getLink() const {
    return link;
}

int Node::getKey() const {
    return key;
}
