#include <iostream>
#include "queue.h"

int main() {
    Queue<int> q;
    q.push(10, 1);
    q.push(12, 2);
    q.push(1, 6);
    q.push(3, 4);
    q.display();
    q.pop();
    std::cout << "The Queue's item with most priority is: " << q.top() << std::endl;
    std::cout << "The number of elements in Queue is: " << q.size() << std::endl;
    q.clear();
    q.display();
    return 0;
}
