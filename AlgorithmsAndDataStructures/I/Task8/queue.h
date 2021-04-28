#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>
#include <cassert>

template <typename T>
struct Node {
    T value;
    int priority;
    Node* next;
    Node() : value(T()), next(nullptr) {}
    Node(const T& item, int p, Node* ptr = nullptr) : value(item), priority(p), next(ptr) {}
    ~Node() {}
};

template <typename T>
class Queue {
    Node<T>* head, * tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue();
    bool empty() const { return head == nullptr; }
    int size() const;
    void pop();
    T& top();
    void push(const T& item, int p);
    void clear();
    void display();
};

template <typename T>
Queue<T>::~Queue() {
    for (Node<T>* node; !empty(); ) {
        node = head->next;
        delete head;
        head = node;
    }
}

template <typename T>
void Queue<T>::push(const T& item, int p) {
    if (empty())
        head = tail = new Node<T>(item, p);
    else if(p > head->priority)
        head = new Node<T>(item, p, head);
    else {
        Node<T>* current = head;
        auto* node = new Node<T>(item, p);
        while (current->next != nullptr && current->next->priority > p) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
}

template <typename T>
void Queue<T>::pop() {
    Node<T>* node = head;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        head = head->next;
    }
    delete node;
}

template <typename T>
void Queue<T>::display() {
    Node<T>* node = head;
    std::cout << "->[ ";
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << "]" << std::endl;
}

template <typename T>
T& Queue<T>::top() { head->value; }

template<typename T>
int Queue<T>::size() const {
    Node<T>* node = head;
    int temp = 0;
    while (node != nullptr) {
        temp++;
        node = node->next;
    }
    return temp;
}

template<typename T>
void Queue<T>::clear() {
    Node<T>* current = head;
    Node<T>* next;

    while (current != nullptr) {
        next = current->next;
        free(current);
        current = next;
    }
    head = nullptr;
}

#endif