#include "List.h"
#include <iostream>

void List::addBeg(int data) {
    if (this->first == nullptr) //jeżeli nie istnieje lista
    {
        Node* link = XOR(nullptr, this->first);
        this->first = new Node(data, link);
        this->last = this->first;
        this->actual = this->first;
    }
    else //jeżeli dodajemy kolejny element do listy
    {
        Node* link = XOR(nullptr, this->first);
        Node* temp = new Node(data, link);
        this->first->setNode(XOR(temp, XOR(this->first->getNode(), nullptr)));
        if (this->first == this->actual)
            this->prev = temp;
        this->first = temp;
    }
}

void List::addEnd(int data) {
    if(this->last == nullptr) //jeżeli nie istnieje lista
    {
        Node* link = XOR(this->last, nullptr);
        this->last = new Node(data, link);
        this->first = this->last;
        this->actual = this->last;
    }
    else //jeżeli dodajemy kolejny element do listy
    {
        Node* link = XOR(this->last, nullptr);
        Node* temp = new Node(data, link);
        this->last->setNode(XOR(XOR(this->last->getNode(), nullptr), temp));
        if (this->actual == this->first)
            this->prev = temp;
        this->last = temp;
    }
}

void List::addActual(int data)
{
    if (this->actual == nullptr) //nie istnieje lista
    {
        addBeg(data);
    }
    else if (this->actual == this->first) //jeżeli aktualny element = pierwszemu musimy przestawić wskaźnik na 1 element
    {
        Node* link = XOR(nullptr, this->actual);
        Node* insert = new Node(data, link);
        this->first->setNode(XOR(insert, XOR(this->first->getNode(), nullptr)));
        this->first = insert;
        this->prev = insert;

    }
    else //dodawanie elementu przed elementem aktualnym
    {
        Node* link = XOR(this->prev, this->actual);
        Node* insert = new Node(data, link);
        this->prev->setNode(XOR(XOR(this->prev->getNode(), this->actual), insert));
        this->actual->setNode(XOR(insert, XOR(this->prev, this->actual->getNode())));
        this->prev = insert;
    }
}

void List::printForward() {
    Node* next;
    Node* temporaryActual = this->first;
    Node* previous = nullptr;
    if (this->first == nullptr) //wydrukuje NULL jezeli lista nie istnieje
        std::cout << "NULL" << std::endl;
    else //wypisywanie elementow od pierszego do ostatniego
    {
        while(temporaryActual != nullptr)
        {
            std::cout << temporaryActual->getData() << " ";
            next = XOR(previous, temporaryActual->getNode());
            previous = temporaryActual;
            temporaryActual = next;
        }
        std::cout << std::endl;
    }
}

void List::printBackward() {
    Node* next;
    Node* temporaryActual = this->last;
    Node* previous = nullptr;
    if (this->first == nullptr) //wydrukuje NULL jezeli lista nie istnieje
        std::cout << "NULL" << std::endl;
    else //wypisywanie elementow od ostaniego do pierwszego
    {
        while(temporaryActual != nullptr)
        {
            std::cout << temporaryActual->getData() << " ";
            next = XOR(temporaryActual->getNode(), previous);
            previous = temporaryActual;
            temporaryActual = next;
        }
        std::cout << std::endl;
    }
}

void List::printActual() const { //wypisywanie aktualnego elementu
    if (this->actual != nullptr)
    {
        std::cout << this->actual->getData() << std::endl;
    }
    else
    {
        std::cout << "NULL" << std::endl;
    }
}

void List::printNext() {
    if (this->actual == nullptr)
    {
        std::cout << "NULL" << std::endl;
    }
    else //wypisywanie nastepnego elementu i zmiana wskaznika z elementu aktualnego na nastepny
    {
        Node* next;
        next = XOR(this->prev, this->actual->getNode());
        if (this->actual == this->last)
        {
            this->prev = this->actual;
            this->actual = this->first;
            std::cout << this->actual->getData() << std::endl;
        }
        else if (this->actual == this->first)
        {
            this->actual = XOR(nullptr, this->actual->getNode());
            this->prev = this->first;
            std::cout << this->actual->getData() << std::endl;
        }
        else
        {
            this->prev = this->actual;
            this->actual = next;
            std::cout << this->actual->getData() << std::endl;
        }
    }
}

void List::printPrevious() {
    if (this->actual == nullptr)
    {
        std::cout << "NULL" << std::endl;
    }
    else //wypisywanie elementu poprzedniego i zamiana wskaznika z elementu aktualnego na poprzedni
    {
        Node* temp = XOR(this->prev->getNode(), this->actual);
        if (this->actual == this->first)
        {
            this->prev = XOR(this->prev->getNode(), nullptr);
            this->actual = this->last;
            std::cout << this->actual->getData() << std::endl;
        }
        else if (this->prev == this->first)
        {
            this->actual = this->prev;
            this->prev = this->last;
            std::cout << this->actual->getData() << std::endl;
        }
        else
        {
            this->actual = this->prev;
            this->prev = temp;
            std::cout << this->actual->getData() << std::endl;
        }
    }
}

void List::deleteBeg() {
    if (this->first != nullptr) //jezeli istnieje lista
    {
        Node* next = XOR(nullptr, this->first->getNode());
        if (next != nullptr)  //jezeli sa chociaz 2 elementy w liscie
        {
            Node* another = XOR(this->first, next->getNode());
            Node* tempLink = XOR(nullptr, another);
            next->setNode(tempLink);
            if (this->actual == this->first)
            {
                this->actual = this->last;
                this->prev = XOR(this->last->getNode(), nullptr);
            }
            if (this->prev == this->first)
                this->prev = this->last;
            delete this->first;
            this->first = next;
        }
        else //jezeli jest tylko jeden element w liscie
        {
            delete this->first;
            this->first = nullptr;
            this->last = nullptr;
            this->actual = nullptr;
            this->prev = nullptr;
        }
    }
}

void List::deleteEnd() {
    if (this->last != nullptr) //istnieje lista
    {
        Node* previous = XOR(this->last->getNode(), nullptr);
        if (previous != nullptr) //sa chociaz 2 elementy
        {
            Node* another = XOR(previous->getNode(), this->last);
            Node* tempLink = XOR(another, nullptr);
            previous->setNode(tempLink);
            if (this->actual == this->last)
            {
                this->actual = previous;
                this->prev = another;
            }
            if (this->prev == this->last)
                this->prev = previous;
            delete this->last;
            this->last = previous;
        }
        else //jest tylko 1 element
        {
            delete this->last;
            this->first = nullptr;
            this->last = nullptr;
            this->actual = nullptr;
            this->prev = nullptr;
        }
    }
}

void List::deleteActual() {
    if (this->actual != nullptr) //istnieje lista
    {
        Node* next = XOR(this->prev, this->actual->getNode());
        if (this->actual == this->first)
        {
            deleteBeg();
        }
        else if (this->actual == this->last)
        {
            deleteEnd();
        }
        else //actual nie jest ani pierwszym ani ostatnim elementem
        {
            next->setNode(XOR(this->prev, XOR(this->actual, next->getNode())));
            this->prev->setNode(XOR(XOR(this->prev->getNode(), this->actual), next));
            delete this->actual;
            this->actual = this->prev;
            if (this->prev == this->first)
                this->prev = this->last;
            else
                this->prev = XOR(this->actual->getNode(), next);
        }
    }
}

void List::deleteValue(int data) {
    Node* next;
    Node* temporaryActual = this->first;
    Node* previous = nullptr;
    while (temporaryActual != this->last) //iteruje przez cala liste elementow
    {
        next = XOR(previous, temporaryActual->getNode());
        if (temporaryActual->getData() == data)
        {
            if (temporaryActual == this->first) //przypadek kiedy wartosc wystepuje w 1 elemencie
            {
                next->setNode(XOR(previous, XOR(temporaryActual, next->getNode())));
                if (temporaryActual == this->actual)
                    this->actual = this->last;
                if (temporaryActual == this->prev)
                    this->prev = this->last;
                this->first = next;
                delete temporaryActual;
                temporaryActual = previous;
            }
            else //znajdujemy element w srodku listy
            {
                next->setNode(XOR(previous, XOR(temporaryActual, next->getNode())));
                previous->setNode(XOR(XOR(previous->getNode(), temporaryActual), next));
                if (temporaryActual == this->actual)
                {
                    this->actual = previous;
                    this->prev = XOR(previous, temporaryActual->getNode());
                }
                if (temporaryActual == this->prev)
                    this->prev = previous;
                delete temporaryActual;
                temporaryActual = previous;
            }
        }
        previous = temporaryActual;
        temporaryActual = next;
    }
    if (temporaryActual->getData() == data && temporaryActual == this->last) //jezeli wartosc wystepuje w ostatnim elemencie
        deleteEnd();
}

Node *List::XOR(Node *left, Node *right)  { //Metoda do określania kolejnych adresów elementów
    return (Node*)((uintptr_t)(left)^(uintptr_t)(right));
}

List::~List() {
    Node* next;
    Node* temporaryActual = this->first;
    Node* previous = nullptr;
    if (this->first)
    {
        while (temporaryActual != nullptr)
        {
            next = XOR(previous, temporaryActual->getNode());
            delete previous;
            previous = temporaryActual;
            temporaryActual = next;
        }
    }
}
