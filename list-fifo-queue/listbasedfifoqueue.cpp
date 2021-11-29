#include "ListBasedFIFOQueue.h"
#include <iostream>

void List::addBeg(int key) {
    if (!this->first) //jezeli lista nie istnieje
    {
        this->first = new Node(key, nullptr);
        this->last = this->first;
        this->first->setLink(this->first);
        this->sizeOfList++;
    }
    else //dodawanie kolejnego elementu do listy
    {
        Node* temp = new Node(key, this->first);
        this->first = temp;
        this->last->setLink(this->first);
        this->sizeOfList++;
    }
}

void List::addEnd(int key) {
    if (!this->first) //lista nie istnieje
    {
        addBeg(key);
    }
    else //dodawanie kolejnego elementu na koniec listy
    {
        Node* temp = new Node(key, this->first);
        this->last->setLink(temp);
        this->last = temp;
        this->sizeOfList++;
    }
}

void List::delBeg() {
    if (this->first) //lista istnieje
    {
        if (this->first == this->last) //lista ma tylko jeden element
        {
            delete this->first;
            this->first = this->last = this->front = this->back = nullptr;
            this->sizeOfList = 0;
        }
        else //lista ma wiecej niz jeden element
        {
            if (this->first == this->front)
                this->front = this->first->getLink();
            if (this->first == this->back)
                this->back = this->first->getLink();
            Node* temp = this->first;
            this->first = this->first->getLink();
            delete temp;
            this->last->setLink(this->first);
            this->sizeOfList--;
        }
    }
}

void List::delEnd() {
    if (this->first) //lista istnieje
    {
        if (this->first == this->last) //lista ma tylko jeden element
            delBeg();
        else //lista ma wiecej niz jeden element
        {
            Node* temp = this->first;
            while (temp->getLink() != this->last)
                temp = temp->getLink();
            if (this->last == this->front)
                this->front = temp;
            if (this->last == this->back)
                this->back = this->first;
            delete this->last;
            this->last = temp;
            this->last->setLink(this->first);
            this->sizeOfList--;
        }
    }
}

void List::printForward() {
    if (this->first) //jezeli istnieje lista wypisywanie kazdego elementu listy od pierwszego do ostatniego
    {
        Node* temp = this->first;
        while (temp != this->last)
        {
            printf("%d ", temp->getKey());
            temp = temp->getLink();
        }
        printf("%d\n", temp->getKey());
    }
    else //jezeli nie istnieje lista
        printf("NULL\n");
}

void backward(Node* start, Node* cmp) //funkcja rekurencyjna do wypisywania listy jednokierunkowej w odwrotnej kolejnosci
{
    if (start->getLink() == cmp) //przypadek poczatkowy jezeli nastepny element bedzie pierwszym elementem listy
    {
        printf("%d ", start->getKey());
        return;
    }
    else
    {
        backward(start->getLink(), cmp);
        printf("%d ", start->getKey());
    }
}

void List::printBackward() {
    if (first) //jezeli istnieje lista
    {
        backward(this->first, this->first);
        printf("\n");
    }
    else //nie istnieje lista
        printf("NULL\n");
}

void backwardCount(Node* start, Node* cmp, int &count) //funkcja rekurencyjna do liczenia w odwrotnnej kolejnosci
{
    if (start->getLink() == cmp) //przypadek poczatkowy jezeli nastepny element bedzie pierwszym elementem listy
    {
        count++;
        return;
    }
    else
    {
        backwardCount(start->getLink(), cmp, count);
        count++;
    }
}

void List::push(int key) {
    if (!this->front) //jezeli nie istnieje kolejka
    {
        if (!this->first) //jezeli nie istnieje lista
        {
            addBeg(key);
            this->front = this->back = this->first;
        }
        else //jezeli jest miejsce w liscie
        {
            this->last->setKey(key);
            this->front = this->back = this->last;
        }
    }
    else //istnieje kolejka
    {
        int count = 0;
        backwardCount(this->back, this->front->getLink(), count);
        if (this->sizeOfList > count) //sa miejsca w liscie
        {
            Node* curr = this->first;
            Node* next = this->first->getLink();
            while (next != this->back)
            {
                curr = next;
                next = next->getLink();
            }
            curr->setKey(key);
            this->back = curr;
        }
        else //nie ma miejsca w liscie
        {
            Node* newNode = new Node(key, this->back);
            if (this->first == this->back)
            {
                this->first = newNode;
            }
            this->front->setLink(newNode);
            this->back = newNode;
            this->sizeOfList++;
        }
    }
}

void List::pop() {
    if(this->front) //jezeli istnieje kolejka
    {
        if (this->front == this->back) //jest tylko jeden element w kolejce
        {
            printf("%d\n", this->front->getKey());
            this->front = this->back = nullptr;
        }
        else //jest wiecej niz jeden element w kolejce
        {
            Node* temp = this->back;
            while (temp->getLink() != this->front)
                temp = temp->getLink();
            printf("%d\n", this->front->getKey());
            this->front = temp;
        }
    }
    else //nie istnieje kolejka
        printf("NULL\n");
}

void List::printQueue() {
    if (this->front) //wypisywanie kolejki w kolejnosci od pierwszego do ostatniego
    {
        backward(this->back, this->front->getLink());
        printf("\n");
    }
    else //jezeli nie istnieje kolejka
        printf("NULL\n");
}

void List::count() { //zwraca wielkosc kolejki
    if (this->front)
    {
        int count = 0;
        backwardCount(this->back, this->front->getLink(), count);
        printf("%d\n", count);

    }
    else
        printf("0\n");
}

void List::garbageSoft() {
    if (this->first && this->front != this->back) //jezeli istnieje lista i jest kilka wartosci w kolejce
    {
        Node* curr = this->front->getLink();
        while (curr != this->back)
        {
            curr->setKey(0);
            curr = curr->getLink();
        }
    }
    else if (!this->front) //jezeli nie istnieje kolejka
    {
        Node* curr = this->first;
        while (curr != this->last)
        {
            curr->setKey(0);
            curr->getLink();
        }
        curr->setKey(0);
    }
}

void List::garbageHard() {
    if (this->first && this->front != this->back) //jezeli istnieje lista i jest kilka wartosci w kolejce
    {
        Node* curr = this->front;
        Node* next = this->front->getLink();
        while (next != this->back) //iteruje po elementach listy ktore nie naleza do kolejki
        {
            if (next == this->first)
            {
                this->first = next->getLink();
                this->last->setLink(this->first);
            }
            if (next == this->last)
            {
                this->last = curr;
                this->last->setLink(this->first);
            }
            curr->setLink(next->getLink());
            delete next;
            this->sizeOfList--;
            next = curr->getLink();
        }
    }
    else if (!this->front) //jezeli nie istnieje kolejka
    {
        Node* curr = this->first;
        Node* next = this->first->getLink();
        while (next != this->last)
        {
            delete curr;
            curr = next;
            next = next->getLink();
        }
        delete next;
        this->first = this->last = nullptr;
        this->sizeOfList = 0;
    }
}

void List::getSize() const { //zwraca wielkosc listy
    printf("%d\n", this->sizeOfList);
}

List::~List() {
    Node* temp = this->first;
    Node* temp2;
    while (temp != this->last)
    {
        temp2 = temp->getLink();
        delete temp;
        temp = temp2;
    }
    delete temp;
}