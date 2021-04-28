#include <iostream>
#include "bsttree.h"

int main() {
    auto *bst = new BinarySearchTree();
    for (auto num : {2, 123, 32, 15, 6, 12, 21}) {
        bst->insert(num);
    }
    std::cout << "Max value: " << bst->find_max()->value << std::endl;
    std::cout << "Min value: " << bst->find_min()->value << std::endl;
    bst->display();
    bst->remove(2);
    bst->remove(123);
    bst->display();
    std::cout << "New root is: " << bst->get_root()->value;
}