//
// Created by Oleg Semenov on 01.12.2020.
//

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "singlelist.h"

template<typename T>
class Stack {
    SingleList<T> arr;
    int m_size;
public:
    Stack(int s = 10) : m_size(s) { SingleList<T>(); }
    ~Stack() { arr.clear(); }
    Stack(const Stack& s) : Stack() {
        arr = s.arr;
    }

    Stack& operator=(const Stack& s) {
        arr = s.arr;
        return *this;
    }

    bool empty() { return  arr.empty(); }
    bool full() { return size() == m_size; }
    int size() { return arr.size(); }
    int max_size() { return m_size; }
    T& top() { return arr.front(); }

    void push(const T& item) {
        arr.push_front(item);
    }
    void pop() {
        arr.pop_front();
    }
    void clear() {
        arr.clear();
    }

    void display() {
        std::cout << ">";
        arr.display();
    }
};

#endif //STACK_H
