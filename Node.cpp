#include "Node.h"
#include <iostream>

Node::Node(int order, bool isLeaf)
{
    this->order = order;
    this->isLeaf = isLeaf;
    this->keys = new int[(2*order)-1];
    this->childPtr = new Node*[2*order];
    this->currNum = 0;
}

void Node::print()
{
    int i;
    for (i = 0; i < this->currNum; i++)
    {
        if (!this->isLeaf) //az dojde do liscia
            childPtr[i]->print();
        printf("%d ", this->keys[i]);
    }
    if (!this->isLeaf)
        this->childPtr[i]->print();
}

void Node::split(int val, Node *node)
{
    int i = 0;
    Node* temp = new Node(node->order, node->isLeaf); //tworze nowy wezel
    temp->currNum = this->order-1;

    if (!node->isLeaf)
    {
        i = 0;
        while (i <= this->order) //jezeli nie jest lisciem kopiuje kopiuje klucze oraz dzieci danego wezla
        {
            temp->keys[i] = node->keys[i+this->order];
            temp->childPtr[i] = node->childPtr[i+this->order];
            ++i;
        }
        temp->childPtr[i] = node->childPtr[i+this->order];
    }
    else //kopiuje klucze danego wezla
    {
        while (i <= this->order)
        {
            temp->keys[i] = node->keys[i+this->order];
            ++i;
        }
    }

    node->currNum = this->order-1; //zmniejszam ilosc kluczy z wezla
    i = this->currNum;
    while (i >= val) //tworze miejsce dla nowych dzieci
    {
        if (i == this->currNum)
            this->childPtr[i+1] = childPtr[i];
        else if (i == val)
            this->keys[i+1] = this->keys[i];
        else
        {
            this->keys[i+1] = this->keys[i];
            this->childPtr[i+1] = childPtr[i];
        }
        --i;
    }

    this->childPtr[val+1] = temp;
    this->keys[val] = node->keys[this->order-1];

    ++this->currNum;
}

void Node::insertToTree(int val)
{
    int index = 0;
    for (; index < this->currNum; index++) //znajduje indeks na ktory wstawie wartosc
    {
        if (this->keys[index] > val)
            break;
    }
    if (!this->isLeaf) //jezeli to nie jest lisc
    {
        if (this->childPtr[index]->currNum == 2*this->order-1) //jezeli dziecko jest pelne
        {
            split(index, this->childPtr[index]);
            if (this->keys[index] < val) //wybieram dla ktorego dziecka ma byc przypisana wartosc
                index++;
        }
        this->childPtr[index]->insertToTree(val); //jezeli dziecko ma miejsce
    }
    else //jezeli to jest lisc
    {
        for (int i = this->currNum-1; i >= index; i--) //przesuwam odpowiednie klucze o jedno miejsce w gore
        {
            this->keys[i+1] = this->keys[i];
        }
        ++this->currNum; //zwiekszam ilosc wartosc
        this->keys[index] = val; //wstawiam klucz
    }
}

Node *Node::search(int val) {
    int index = 0;
    for (; index < this->currNum; index++)
    {
        if (val <= this->keys[index])
            break;
    }

    if (this->keys[index] == val)
        return this;

    if (this->isLeaf)
        return nullptr;

    return this->childPtr[index]->search(val);
}

void Node::loadToTree(char *input, int &i)
{
    int j = 0;
    int k = 0;
    while (input[i] != '\0')
    {
        i++;
        if (input[i-1] == '(')
        {
            Node* temp = new Node(this->order, true);
            this->isLeaf = false;
            this->childPtr[k] = temp;
            k++;
            temp->loadToTree(input, i);
        }
        else if (input[i-1] == ')')
            return;
        else if (input[i-1] != ' ')
        {
            if (input[i] != ')' && input[i] != '(' && input[i] != ' ' && input[i+1] != ')' && input[i+1] != '(' && input[i+1] != ' ')
            {
                char temp[3];
                temp[0] = input[i-1];
                temp[1] = input[i];
                temp[2] = input[i+1];
                int key = (int(temp[0] - '0') * 100 + int(temp[1] - '0') * 10 + int(temp[2] - '0'));
                this->keys[j] = key;
                i += 2;
            }
            else if (input[i] != ')' && input[i] != '(' && input[i] != ' ')
            {
                char temp[2];
                temp[0] = input[i-1];
                temp[1] = input[i];
                int key = (int(temp[0] - '0') * 10) + int(temp[1] - '0');
                this->keys[j] = key;
                i++;
            }
            else
            {
                this->keys[j] = input[i-1]-48;
            }
            j++;
            this->currNum++;
        }
    }
}

void Node::saveTree()
{
    int i;
    printf("( ");
    for (i = 0; i < this->currNum; i++)
    {
        if (!this->isLeaf)
            childPtr[i]->saveTree();
        printf("%d ", this->keys[i]);
    }
    if (!this->isLeaf)
        this->childPtr[i]->saveTree();
    printf(") ");
}
