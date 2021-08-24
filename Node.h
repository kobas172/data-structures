class Node {
public:
    bool isLeaf;
    int *keys;
    Node **childPtr;
    int currNum;
    int order;
    Node(int order, bool isLeaf);

    void print();
    void split(int val, Node* node);
    void insertToTree(int val);
    Node* search(int val);
    void loadToTree(char input[], int &i);
    void saveTree();
};
