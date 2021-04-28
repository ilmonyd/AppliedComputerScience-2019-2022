// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
    // the default access mode and default inheritance mode are public
    T value;
    DoubleNode* next, * prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode* nptr = nullptr, DoubleNode* pptr = nullptr)
            : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T>* head, * tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly
    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);
    DoubleList(DoubleList&& other); // move constructor
    // usage:   DoubleList<int> list2(std::move(list1));
    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;
    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1);
    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1)
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1)
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)
};

template<typename T>
DoubleList<T>::~DoubleList(){ // tu trzeba wyczyscic wezly
    for (DoubleNode<T>* node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
}

template<typename T>
DoubleList<T>::DoubleList(const DoubleList& other) { // copy constructor
    // usage:   DoubleList<int> list2(list1);
    assert(!other.empty());
    head = nullptr;
    tail = nullptr;
    DoubleNode<T>* current = other.head;
    while (current != nullptr) {
        if (head == nullptr) {  //dla pierwszego wezla
            head = tail = new DoubleNode<T>(current->value);
        }
        else {
            tail->next = new DoubleNode<T>(current->value);
            tail->next->prev = tail;
            tail = tail->next;
        }
        current = current->next;
    }
}

template<typename T>
DoubleList<T>::DoubleList(DoubleList&& other) { // move constructor
    // usage:   DoubleList<int> list2(std::move(list1));
    head = nullptr;
    tail = nullptr;
    head = std::move(other.head);
    other.head = nullptr;
    tail = std::move(other.tail);
    other.tail = nullptr;
}

template<typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& dl){
    assert(!dl.empty());
    head = nullptr;
    tail = nullptr;
    DoubleNode<T>* current = dl.head;

    while (current != nullptr) {
        if (head == nullptr) {
            head = tail = new DoubleNode<T>(current->value);
        }
        else {
            tail->next = new DoubleNode<T>(current->value);
            tail->next->prev = tail;
            tail = tail->next;
        }
        current = current->next;
    }
    return *this;
}

template<typename T>
inline DoubleList<T>& DoubleList<T>::operator=(DoubleList&& dl){
    head = nullptr;
    tail = nullptr;
    head = std::move(dl.head);
    dl.head = nullptr;
    tail = std::move(dl.tail);
    dl.tail = nullptr;
    return *this;
}


template<typename T>
inline int DoubleList<T>::size() const{
    DoubleNode<T>* current = tail;
    int count = 0;
    while (current != nullptr) {
        count++;
        current = current->prev;
    }
    std::cout << std::endl;
    return count;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    }
    else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    }
    else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template<typename T>
void DoubleList<T>::push_back(const T& item){
    if (!empty()) {
        tail->next = new DoubleNode<T>(item);
        tail->next->prev = tail;
        tail = tail->next;
    }
    else {
        head = tail = new DoubleNode<T>(item);
    }
}

template<typename T>
void DoubleList<T>::push_back(T&& item){
    if (!empty()) {
        tail->next = new DoubleNode<T>(std::move(item));
        tail->next->prev = tail;
        tail = tail->next;
    }
    else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template<typename T>
void DoubleList<T>::pop_front(){
    DoubleNode<T>* node = head;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        head = head->next;
        head->prev = nullptr;
    }
    delete node;
}

template<typename T>
void DoubleList<T>::pop_back(){
    DoubleNode<T>* node = tail;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        DoubleNode<T>* before = head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}

template<typename T>
void DoubleList<T>::clear(){
    DoubleNode<T>* current = head;
    while (current != nullptr){
        DoubleNode<T>* del = current;
        current = current->next;
        delete del;
    }
    head = tail = nullptr;
}

template<typename T>
void DoubleList<T>::display(){
    DoubleNode<T>* node = head;
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template<typename T>
void DoubleList<T>::display_reversed(){
    DoubleNode<T>* node = tail;
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->prev;
    }
    std::cout << std::endl;
}

#endif

// EOF