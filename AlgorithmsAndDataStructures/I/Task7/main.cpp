#include <iostream>
#include "queue.h"

int main() {
    Queue<int> q(6);
    for (auto i : {1, 2, 3, 10, 12, 13}) q.push(i);
    q.display();
    if (q.full()) std::cout << "Queue is full" << std::endl;
    else std::cout << "Queue is not full" << std::endl;
    std::cout << "Queue's front is: " << q.front() << std::endl;
    std::cout << "Number of elements in Queue: " << q.size() << std::endl;
    q.pop();
    q.display();
    q.clear();
    std::cout << "Queue cleared" << std::endl;
    q.display();
    if (q.empty()) std::cout << "Queue is empty" << std::endl;
    else std::cout << "Queue is not empty" << std::endl;
    return 0;
}
