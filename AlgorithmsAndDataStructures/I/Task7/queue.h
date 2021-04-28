#ifndef Queue_H
#define Queue_H

template <typename T>
class Queue {
private:
     T *tab;
     int msize, head, tail;
public:
     Queue (int s): head(0), tail(0), msize(s+1) { tab = new T[s+1]; };
     ~Queue() { delete[] tab; };
     void push(const T& item);
     void pop();
     T& front();
     int size(); 
     bool empty();
     bool full();
     void clear();
     void display();
};

template <typename T>
void Queue<T>::push(const T& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void Queue<T>::pop() {
     tab[head++ % msize];
}

template <typename T>
T& Queue<T>::front() {
     return tab[head % msize];
}

template <typename T> 
int Queue<T>::size() {
    return (tail - head + msize) % msize;
}

template <typename T>
bool Queue<T>::empty() {
     return tail == head;
}

template <typename T>
bool Queue<T>::full() {
     return (head + msize -1) % msize == tail;
}

template<typename T>
void Queue<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
void Queue<T>::display() {
    std::cout << "-> ";
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

#endif
