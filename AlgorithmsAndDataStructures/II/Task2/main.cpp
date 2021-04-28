#include "pqueue.cpp"

int main() {
    PriorityQueue<int> q;

    q.enqueue(1, 2137);
    q.enqueue(3, 420);
    q.enqueue(2, 47);
    q.enqueue(3,20);
    q.enqueue(2, 22);
    q.enqueue(1, 10000);

    std::cout << q.dequeue().value << std::endl;
    std::cout << q.front().value << std::endl;

    for (int i = 0; i < q.size(); i++){
        std::cout << q[i].value << " ";
    }
}