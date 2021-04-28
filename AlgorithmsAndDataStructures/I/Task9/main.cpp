#include "tree.h"
#include <iostream>

int N = 5;

int main() {
    RandomBinaryTree bt;
    int x;
    std::cout << "Enter 5 numbers: " << std::endl;
    for(int i = 0; i < N; i++) {
        cin >> x;
        bt.insert(x);
    }

    bt.display_rev(bt.getRoot(), 0);
    std::cout << "Binary tree height: " << bt.calc_height(bt.getRoot()) << std::endl << std::endl;
    std::cout << "Leaf count (recur.): " << bt.get_leaf_count_recursive(bt.getRoot()) << std::endl;
    std::cout << "Leaf count (iter.): " << bt.getLeafCount(bt.getRoot()) << std::endl << std::endl;
    std::cout << "Preorder: " << std::endl;
    bt.preorder(bt.getRoot());
    std::cout << "Inorder: " << std::endl;
    bt.inorder(bt.getRoot());
    std::cout << "Postorder: " << std::endl;
    bt.postorder(bt.getRoot());
    std::cout << std::endl;
    bt.clear(bt.getRoot());
    bt.display();
    return 0;
}