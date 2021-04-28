#include <iostream>
#include "queue.h"

using namespace std;

class RandomBinaryTree {
public:
    struct BSTNode {
        int key;
        BSTNode *left;
        BSTNode *right;
    };

private:
    BSTNode *root;
    int nodesCount;
    int max(int a, int b) {
        return (a > b ? a : b);
    };

public:
    RandomBinaryTree() {
        nodesCount = 0;
        root = nullptr;
    };

    ~RandomBinaryTree() {
        clear(root);
    };

    void clear(BSTNode *n) {
        if (n == nullptr) return;
        clear(n->left);
        clear(n->right);
        delete n;
        root = nullptr;
        nodesCount = 0;
    };

    void insert(int x) {
        if (root == nullptr) {
            root = new BSTNode;
            root->key = x;
            root->right = nullptr;
            root->left = nullptr;
            nodesCount++;
        } else {
            BSTNode *temp, *actualNode = root;
            while (actualNode != nullptr) {
                temp = actualNode;
                if (actualNode->key > x)
                    actualNode = actualNode->left;
                else if (actualNode->key <= x)
                    actualNode = actualNode->right;
            }
            actualNode = new BSTNode;
            actualNode->left = nullptr;
            actualNode->right = nullptr;
            actualNode->key = x;
            nodesCount++;
            if (temp->key > x) temp->left = actualNode;
            else temp->right = actualNode;
        }
    };


    int calc_height(BSTNode *n) {
        if (n == nullptr) return 0;
        int length_left = calc_height(n->left);
        int length_right = calc_height(n->right);
        return 1 + max(length_left, length_right);
    };


    void display_rev(BSTNode *node, int level) {
        if (node == nullptr) return;
        display_rev(node->right, level + 1);
        std::cout << std::string(3 * level, ' ') << node->key << std::endl;
        display_rev(node->left, level + 1);
    }

    void display() {
        if (nodesCount == 0) {
            cout << "Binary tree has no elements!" << endl;
            return;
        } else {
            BSTNode *stack[nodesCount];
            BSTNode *temp = root;
            int top = 0;
            while (temp != nullptr || top > 0) {
                while (temp != nullptr) {
                    stack[top++] = temp;
                    temp = temp->left;
                }
                temp = stack[--top];
                cout << temp->key << endl;
                temp = temp->right;
            }
        }
    };

    void preorder(BSTNode *n) {
        cout << n->key << endl;
        if (n->left != nullptr) preorder(n->left);
        if (n->right != nullptr) preorder(n->right);
    };

    void postorder(BSTNode *n) {
        if (n->left != nullptr) postorder(n->left);
        if (n->right != nullptr) postorder(n->right);
        cout << n->key << endl;
    };

    void inorder(BSTNode *n) {
        if (root == nullptr) {
            return;
        } else {
            if (n->left != nullptr) inorder(n->left);
            cout << n->key << endl;
            if (n->right != nullptr) inorder(n->right);
        }
    };

    int get_leaf_count_recursive(BSTNode *node) {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        else return get_leaf_count_recursive(node->left) + get_leaf_count_recursive(node->right);
    };

    int getLeafCount(BSTNode *node) {
        if (!node) return 0;
        Queue<BSTNode *> q(nodesCount);
        int count = 0;
        q.push(node);
        while (!q.empty()) {
            struct BSTNode *temp = q.front();
            q.pop();
            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);
            if (temp->left == nullptr && temp->right == nullptr)
                count++;
        }
        return count;
    };

    BSTNode *getRoot() {
        return root;
    };
};