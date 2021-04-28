#include "set.h"
#include <algorithm>


int set::getSize() {
    return vec.size();
}

void set::printSet() {
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

bool set::isInSet(int x) {
    return (std::find(vec.begin(), vec.end(), x) != vec.end());
}

void set::insert(int x) {
    if (!isInSet(x)) {
        vec.push_back(x);
    }
}

void set::withdraw(int x) {
    if (isInSet(x)) {
        vec.erase(std::remove(vec.begin(), vec.end(), x), vec.end());
    }
    else {
        std::cout << "Element not found in Set" <<std::endl;
    }
}

set set::operator+(set &obj) {
    set temp;
    for (auto i : vec) {
        temp.insert(i);
    }
    for (auto i : obj.vec) {
        temp.insert(i);
    }
    return temp;
}

set set::operator-(set &obj) {
    set temp;
    for (auto i : obj.vec) {
        if (!isInSet(i)) {
            temp.insert(i);
        }
    }
    return temp;
}

set set::operator*(set &obj) {
    set temp;
    for (auto i : vec) {
        if (obj.isInSet(i)) {
            temp.insert(i);
        }
    }
    return temp;
}

bool set::operator==(set &obj) {
    return (getSize() == (this->operator*(obj)).getSize());
}

bool set::operator<=(set &obj) {
    return (0 < (this->operator*(obj)).getSize()) && (getSize() <= obj.getSize());
}

