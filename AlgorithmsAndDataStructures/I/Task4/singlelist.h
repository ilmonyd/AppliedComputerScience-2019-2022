// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct SingleNode {
    // the default access mode and default inheritance mode are public
    T value;
    SingleNode* next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode* ptr = nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T>* head, * tail;
public:
    SingleList() : head(nullptr), tail(nullptr) {}
    ~SingleList(); // tu trzeba wyczyscic wezly
    SingleList(const SingleList& other); // copy constructor
    // usage:   SingleList<int> list2(list1);
    SingleList(SingleList&& other); // move constructor
    // usage:   SingleList<int> list2(std::move(list1));
    SingleList& operator=(const SingleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;
    SingleList& operator=(SingleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1);
    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1), L.push_front(std::move(item))
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1), L.push_back(std::move(item))
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void reverse(); // O(n)
    // Operacje z indeksami.
    int erase(int pos); // return Iterator following the last removed element,
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    int insert(int pos, const T& item); // inserts item before pos,
    // zwraca pozycje wstawionego elementu
};

template <typename T>
SingleList<T>::~SingleList() {
    for (SingleNode<T>* node; !empty(); ) {
        node = head->next;
        delete head;
        head = node;
    }
}

template <typename T>
void SingleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    }
    else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    }
    else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::display() {
    SingleNode<T>* node = head;
    std::cout << "[ ";
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void SingleList<T>::pop_front() {
    SingleNode<T>* node = head;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        head = head->next;
    }
    delete node;
}

template <typename T>
void SingleList<T>::pop_back() {
    SingleNode<T>* node = tail;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        SingleNode<T>* before = head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}

template<typename T>
SingleList<T>::SingleList(const SingleList& other) {
    assert(!other.empty());
    head = nullptr;
    tail = nullptr;
    SingleNode<T>* current = other.head;

    while (current != nullptr) {
        if (head == nullptr) {
            head = tail = new SingleNode<T>(current->value);
        }
        else {
            tail->next = new SingleNode<T>(current->value);
            tail = tail->next;
        }
        current = current->next;
    }
}

template<typename T>
SingleList<T>::SingleList(SingleList&& other) {
    head = nullptr;
    tail = nullptr;
    head = std::move(other.head);
    other.head = nullptr;
    tail = std::move(other.tail);
    other.tail = nullptr;
}

template<typename T>
SingleList<T>& SingleList<T>::operator=(const SingleList& other) {
    assert(!other.empty());
    head = nullptr;
    tail = nullptr;
    SingleNode<T>* current = other.head;

    while (current != nullptr) {
        if (head == nullptr) {
            head = tail = new SingleNode<T>(current->value);
        }
        else {
            tail->next = new SingleNode<T>(current->value);
            tail = tail->next;
        }
        current = current->next;
    }
    return *this;
}

template<typename T>
SingleList<T>& SingleList<T>::operator = (SingleList&& sl) {
    head = nullptr;
    tail = nullptr;
    head = std::move(sl.head);
    sl.head = nullptr;
    tail = std::move(sl.tail);
    sl.tail = nullptr;
    return *this;
}

template<typename T>
int SingleList<T>::size() const {
    SingleNode<T>* node = head;
    int temp = 0;
    while (node != nullptr) {
        temp++;
        node = node->next;
    }
    return temp;
}

template<typename T>
void SingleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new SingleNode<T>(std::move(item), head);
    }
    else {
        head = tail = new SingleNode<T>(std::move(item));
    }
}

template<typename T>
void SingleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(std::move(item));
        tail = tail->next;
    }
    else {
        head = tail = new SingleNode<T>(std::move(item));
    }
}

template<typename T>
void SingleList<T>::clear() {
    SingleNode<T>* current = head;
    SingleNode<T>* next;

    while (current != nullptr) {
        next = current->next;
        free(current);
        current = next;
    }
    head = nullptr;
}

template<typename T>
void SingleList<T>::reverse() {
    assert(!empty());
    SingleNode<T>* next = nullptr;
    SingleNode<T>* prev = nullptr;
    SingleNode<T>* cur = head;

    while (cur != nullptr) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
}

template<typename T>
int SingleList<T>::erase(int pos) {
    assert(!empty());
    SingleNode<T>* node = head;
    if (pos == 0) {
        node = head->next;
        delete head;
        head = node;
    }
    else if ((pos > 0) && (pos < size())) {
        int temp = 1;
        while (node != nullptr) {
            if (temp == pos) {
                SingleNode<T>* prev = node;
                SingleNode<T>* cur = node->next;
                SingleNode<T>* next = cur->next;
                delete cur;
                prev->next = next;
                break;
            }
            temp++;
            node = node->next;
        }
        return node->value;
    }
    else {
        SingleNode<T>* prev = head;
        while (prev->next != tail) {
            prev = prev->next;
        }
        tail = prev;
        tail->next = nullptr;
        return node->value;
    }
    return node->value;
}

template<typename T>
T& SingleList<T>::operator[](int pos) {
    assert(!empty() && (pos < size()));
    int temp = 0;
    SingleNode<T>* node = head;
    while (node != nullptr) {
        if (temp == pos) {
            break;
        }
        temp++;
        node = node->next;
    }
    return node->value;
}

template<typename T>
const T& SingleList<T>::operator[](int pos) const {
    assert(!empty() && (pos < size()));
    int temp = 0;
    SingleNode<T>* node = head;
    while (node != nullptr) {
        if (temp == pos) {
            break;
        }
        temp++;
        node = node->next;
    }
    return node->value;
}

template<typename T>
int SingleList<T>::index(const T& item) {
    assert(!empty());
    int temp = 0;
    SingleNode<T>* node = head;
    while (node != nullptr) {
        if (node->value == item) {
            return temp;
        }
        temp++;
        node = node->next;
    }
    return -1;
}

template<typename T>
int SingleList<T>::insert(int pos, const T& item) {
    SingleNode<T>* node = head;
    if (pos == 0) {
        node = new SingleNode<T>(item, node);
        return node->value;
    }
    else if ((0 < pos) && (pos < size())) {
        int temp = 1;
        while (node != nullptr) {
            if (temp == pos) {
                node->next = new SingleNode<T>(item, node->next);
                break;
            }
            temp++;
            node = node->next;
        }
        return node->value;
    }
    else {
        std::cout << "index is greater than the SingleList"<< std::endl;
        return node->value;
    }
}
#endif