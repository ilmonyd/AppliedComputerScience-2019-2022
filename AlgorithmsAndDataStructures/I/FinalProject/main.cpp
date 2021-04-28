#include <iostream>
#include "heap.cpp"

#define IS_TRUE(x) {temp &= x; if (!x) {std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }}


void unit_test() {
    Heap<size_t> heap({5, 2, 4, 1, 3}, 3);
    bool temp = true;
    IS_TRUE((heap.front() == 1))
    IS_TRUE((heap.size() == 5))
    IS_TRUE((heap[2] == 4))
    IS_TRUE(!heap.empty())
    heap.insert(6);
    IS_TRUE((heap[heap.size() - 1] == 6))
    int extracted = heap.extract();
    IS_TRUE((extracted == 1))
    IS_TRUE((heap.front() == 2))
    if (temp) {std::cout << "All unit tests passed.";}
}

int main() {
    Heap<size_t> heap_min({5, 2, 4, 1, 3}, 3, HeapType::MIN), heap_max({5, 2, 4, 1, 3}, 3, HeapType::MAX);
    std::cout << "The heap's front: " << heap_min.front() << std::endl;
    for (int i = 0; i < heap_min.size(); i++) {
        std::cout << heap_min[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "The heap's front: " << heap_max.front() << std::endl;
    for (int i = 0; i < heap_max.size(); i++) {
        std::cout << heap_max[i] << std::endl;
    }
    std::cout << std::endl;
    unit_test();
    return 0;
}
