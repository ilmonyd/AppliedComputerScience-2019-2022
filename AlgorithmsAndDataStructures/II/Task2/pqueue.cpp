#include <initializer_list>
#include <iostream>
#include <vector>

template<typename T>
class PriorityQueue {
    struct Item {
        int priority;
        T value;
    };

    std::vector<Item> data;

    size_t parent(size_t i) const {
        return (i - 1) / 2;
    }

    size_t child(size_t i, size_t n) const {
        return i * 2 + n + 1;
    }

    void heapify(size_t i) {
        auto top = i;

        for (size_t n = 0; n < 2 && child(i, n) < data.size(); n++) {
            if (data[child(i, n)].priority > data[top].priority) {
                top = child(i, n);
            }
        }

        if (top != i) {
            std::swap(data[top], data[i]);
            heapify(top);
        }
    }

public:
    PriorityQueue(std::initializer_list<T> init_data)
            : data(init_data) {
        for (size_t i = data.size() / 2; i-- > 0;) {
            heapify(i);
        }
    }

    explicit PriorityQueue() = default;

    void enqueue(int priority, T value) {
        enqueue(Item{priority, value});
    }

    void enqueue(Item item) {
        auto index = data.size();
        data.push_back(item);

        while (index > 0) {
            auto p = parent(index);
            if (data[index].priority > data[p].priority) {
                std::swap(data[p], data[index]);
            }
            index = p;
        }
    }

    Item dequeue() {
        auto top = data.at(0);
        data.front() = data.back();
        data.pop_back();
        heapify(0);
        return top;
    }

    Item front() const {
        return data.front();
    }

    Item operator[](size_t i) const {
        return data[i];
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};