#include <initializer_list>
#include <iostream>
#include <vector>

enum class HeapType {
    MIN,
    MAX
};

template<typename T>
class Heap {
    std::vector<T> data;
    const size_t d;
    const HeapType type;

    size_t parent(size_t i) const {
        return (i - 1) / d;
    }

    size_t child(size_t i, size_t n) const {
        return i * d + n + 1;
    }

    bool cmp(T a, T b) const {
        return type == HeapType::MIN ? a < b : a > b;
    }

    void heapify(size_t i) {
        auto top = i;

        for (size_t n = 0; n < d && child(i, n) < data.size(); n++) {
            if (cmp(data[child(i, n)], data[top])) {
                top = child(i, n);
            }
        }

        if (top != i) {
            std::swap(data[top], data[i]);
            heapify(top);
        }
    }

public:
    Heap(std::initializer_list<T> init_data, size_t d = 3, HeapType type = HeapType::MIN)
            : data(init_data), d(d), type(type) {
        for (size_t i = data.size() / 2; i-- > 0;) {
            heapify(i);
        }
    }

    explicit Heap(size_t d = 3, HeapType type = HeapType::MIN)
            : d(d), type(type) {}

    void insert(T key) {
        auto index = data.size();
        data.push_back(key);

        while (index > 0) {
            auto p = parent(index);
            if (cmp(data[index], data[p])) {
                std::swap(data[p], data[index]);
            }
            index = p;
        }
    }

    T extract() {
        auto top = data.at(0);
        data.front() = data.back();
        data.pop_back();
        heapify(0);
        return top;
    }

    T front() const {
        return data.front();
    }

    T operator[](size_t i) const {
        return data[i];
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};