//
// Created by Oleg Semenov on 01.12.2020.
//

#include <iostream>
#include "stack.h"

int main() {
    Stack<int> s1(3);
    s1.push(11);
    s1.push(10);
    s1.push(12);
    std::cout << "Stack s1: ";
    s1.display();
    s1.pop();
    Stack<int> s2 = s1;
    std::cout << "Stack s2: ";
    s2.display();
    std::cout << "Size of Stack s1: " << s1.size() << std::endl;
    if (s1.full()) {
        std::cout << "Stack s1 is full\n";
    }
    else {
        std::cout << "Stack s1 is not full\n";
    }
    std::cout << "The top element of Stack s1 is: " << s1.top() << std::endl;
    if (s2.empty()) {
        std::cout << "Stack s2 is empty\n";
    }
    else {
        std::cout << "Stack s2 is not empty\n";
    }
    s2.clear();
    if (s2.empty()) {
        std::cout << "Stack s2 is empty\n";
    }
    else {
        std::cout << "Stack s2 is not empty\n";
    }
    return 0;
}
