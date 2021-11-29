#include "Node.h"

Node::Node() {
    this->data=0;
    this->node=nullptr;
}

Node::Node(int data, Node *node) {
    this->data = data;
    this->node = node;
}

void Node::setNode(Node *node) {
    this->node = node;
}

Node *Node::getNode() const {
    return node;
}

int Node::getData() const {
    return data;
}
