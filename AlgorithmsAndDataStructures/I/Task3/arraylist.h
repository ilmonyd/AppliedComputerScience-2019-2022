#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <cassert>


//
//  Created by Oleg Semenov on 29.10.2020
//


template<typename T>
class ArrayList {
private:
    std::unique_ptr<T[]> tab;
    int last, msize;

public:
    explicit ArrayList(int s=10) : msize(s), last(0) {
        tab = std::make_unique<T[]>(s);
        assert( tab != nullptr );
    }
//    ~ArrayList() {
//        delete [] tab;
//    }
    bool full();
    bool empty();
    int size();
    T & front();
    T & back();
    void push_front(T);
    void push_back(T);
    void pop_front();
    void pop_back();
    int find(T);
    int insert(int, T);
    int erase(int);
    void clear();
    void merge(ArrayList& other);
    void reverse();
    void sort();
    friend std::ostream& operator <<(std::ostream& out, ArrayList<T>& list) {
        out << "[";
        if (!list.empty()) {
            out << list.front();
            for (int i = 1; i < list.size(); i++) {
                out << ", " << list.tab[i];
            }
        }
        out << "]";
        return out;
    };
    T operator[](int i) {
        return tab[i];
    }
};


template<typename T>
bool ArrayList<T>::full() {
    return last == msize;
}

template<typename T>
int ArrayList<T>::size() {
    return last;
}

template<typename T>
bool ArrayList<T>::empty() {
    return last == 0;
}

template<typename T>
void ArrayList<T>::push_front(T x) {
    int i;
    for(i = size(); i > 0; i--) {
        tab[i] = tab[i-1];
    }
    tab[0] = x;
    last++;
}

template<typename T>
void ArrayList<T>::push_back(T elem) {
    tab[last++] = elem;
}

template<typename T>
void ArrayList<T>::pop_back() {
    if(!empty()) {
        last--;
    }
}

template<typename T>
T& ArrayList<T>::front() {
    return tab[0];
}

template<typename T>
T& ArrayList<T>::back() {
    return tab[last];
}

template<typename T>
void ArrayList<T>::clear() {
    int n = size();
    last = 0;
    msize = n;
    tab = std::make_unique<T[]>(n);
}

template<typename T>
void ArrayList<T>::reverse() {
    for(int start = 0, end = size() - 1; start < end; start++, end--){
        std::swap(tab[start], tab[end]);
    }
}

template<typename T>
void ArrayList<T>::sort() {
    int n;
    n = size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (tab[j] > tab[j+1]) {
                std::swap(tab[j], tab[j+1]);
            }
        }
    }
}

template<typename T>
void ArrayList<T>::pop_front() {
    if(!empty()) {
        for (int i = 1; i < size(); i++) {
            tab[i - 1] = tab[i];
        }
        last--;
    }
}

template<typename T>
int ArrayList<T>::find(T x) {
    int n = size();
    for(int i = 0; i < n; i++) {
        if(tab[i] == x) return i;
    }
    return -1;
}

template<typename T>
int ArrayList<T>::insert(int pos, T x) {
    if(!(pos < 1 || pos > size()+1)) {
        int i = 0;
        for(i = size()+1; i >= pos; i--) {
            tab[i] = tab[i-1];
        }
        tab[pos-1] = x;
        last++;
        return pos-1;
    } else return -1;
}

template<typename T>
int ArrayList<T>::erase(int x) {
    int n = size();
    if(x < 0) return -1;
    else if(x >= n-1) {
        pop_front();
        return x+1;
    } else {
        for(int i = x; i < n; i++) {
            tab[i] = tab[i+1];
        }
        last--;
        return x+1;
    }
}

template<typename T>
void ArrayList<T>::merge(ArrayList<T>& other) {
    auto temp = std::make_unique<T[]>(size() + other.size());
    std::copy(&tab[0], &tab[size()], &temp[0]);
    std::copy(&other.tab[0], &other.tab[other.size()], &temp[size()]);
    msize = last = size() + other.size();
    tab = std::move(temp);
}

#endif