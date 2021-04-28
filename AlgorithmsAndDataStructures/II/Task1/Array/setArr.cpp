#include "setArr.h"


bool setArr::checkRangeCorrectness(int x) {
    return x < universeSize;
}


setArr::setArr() {
    table = new int[universeSize];
    size = 0;
}

void setArr::insert(int x) {
    if (!isInSet(x) && checkRangeCorrectness(x)) {
        table[size] = x;
        size++;
    }
}

bool setArr::isInSet(int element) {
    for (int i = 0; i < getSize(); i++) {
        if (table[i] == element)
            return true;
    }
    return false;
}


void setArr::printSet() {
    for (int i = 0; i < getSize(); i++) {
        std::cout << table[i] << " ";
    }
    std::cout << std::endl;
}

void setArr::withdraw(int x) {
    if (isInSet(x)) {
        for (int i = 0; i < getSize(); i++) {
            if (table[i] == x) {
                for (int j = i; j < (getSize() - 1); j++) {
                    table[j] = table[j + 1];
                }
                break;
            }
        }
        size--;
    } else {
        std::cout << "Element not found in Set";
    }
}

void setArr::clearSet() {
    for (int i = 0; i < getSize(); ++i) {
        withdraw(table[i]);
    }
}

int setArr::getSize() {
    return size;
}

setArr setArr::operator+(setArr &object) {
    setArr result;
    for (int i = 0; i < getSize(); i++) {
        result.insert(table[i]);
    }
    for (int i = 0; i < object.getSize(); i++) {
        result.insert(object.table[i]);
    }
    return result;
}

setArr setArr::operator-(setArr &object) {
    setArr result;
    for (int i = 0; i < object.getSize(); i++) {
        int val = object.table[i];
        if (!isInSet(val)) {
            result.insert(val);
        }
    }
    return result;
}

setArr setArr::operator*(setArr &object) {
    setArr result;
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < object.getSize(); j++) {
            if(table[i]==object.table[j])
            {
                result.insert(table[i]);
                break;
            }
        }
    }
    return result;
}

bool setArr::operator==(setArr &object) {
    return (getSize() == (this->operator*(object)).getSize());
}

bool setArr::operator<=(setArr &object) {
    return (0 < (this->operator*(object)).getSize()) && (getSize() <= object.getSize());
}
