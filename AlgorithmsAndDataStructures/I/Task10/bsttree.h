#ifndef BinarySearchTree_H
#define BinarySearchTree_H

using namespace std;

struct BSTNode {
    int value;
    BSTNode *right;
    BSTNode *left;
    explicit BSTNode(int value) {
        this->value = value;
        this->right = nullptr;
        this->left = nullptr;
    }
};

class BinarySearchTree {
    public:
        BSTNode *root;
        static void insert(BSTNode *root, int value);
        bool remove(BSTNode *parent, BSTNode *current, int value);
        static BSTNode* nextLarger(BSTNode *node);
        BSTNode* search(int value);
        static void display(BSTNode *root);
        void insert(int value);
        void remove(int item);
        static BSTNode* remove(BSTNode *node);
        BSTNode* find_min();
        BSTNode* find_max();
        BSTNode* get_root();
        void display();
};

BSTNode* BinarySearchTree::search(int value) {
    BSTNode *current = root;
    while (current) {   
        if (current->value == value)
            break;
        if (value > current->value)
            current = current->right;
        else
            current = current->left;
    }
    return current;
}

BSTNode* BinarySearchTree::nextLarger(BSTNode *node) {
    BSTNode *nextLarger = node->right;
    while (nextLarger->left) {
        nextLarger = nextLarger->left;
    }
    return nextLarger;
}
void BinarySearchTree::insert(BSTNode *root, int value) {
    
    if (value > root->value) {
        if (!root->right)
            root->right = new BSTNode(value);
        else
            insert(root->right, value);
    }
    else {
        if (!root->left)
            root->left = new BSTNode(value);
        else
            insert(root->left, value);
    }
}
void BinarySearchTree::insert(int value) {
    
    if (!root) {
        root = new BSTNode(value);
    }
    else {
        this->insert(root, value);
    }

}

bool BinarySearchTree::remove(BSTNode *parent, BSTNode *current, int value) {
    if (!current) {
        return false;
    }
    if (current->value == value) {
        if (!current->left && !current->right)
        {
            if (parent->right == current) {
                parent->right = nullptr;
            }
            else {
                parent->left = nullptr;
            }
            delete current;
            return true;
        }
        else if (!current->left || !current->right) {
            BSTNode *child = current->left;
            if (!child) {
                child = current->right;
            }

            if (!parent) {
                this->root = child;
            }
            else {
                if (child->value > parent->value) {
                    parent->right = child;
                }
                else {
                    parent->left = child;
                }
            }
            delete current;
        }
        
        else {
            BSTNode *largerNode = nextLarger(current);
            current->value = largerNode->value;
            delete largerNode;
        }
        return true;
    }

    if (value > current->value) {
        return remove(current, current->right, value);
    } else {
        return remove(current, current->left, value);
    }
}

void BinarySearchTree::display(BSTNode* root) {
    if (!root)
        return;
    display(root->left);
    cout<<root->value<<" ";
    display(root->right);
}

void BinarySearchTree::display() {
    if(!root)
        return;
    display(root);
    cout << endl;
}

BSTNode* BinarySearchTree::find_max() {
    BSTNode *max = root;
    while (max->right) {
        max = max->right;
    }
    return max;
}

BSTNode* BinarySearchTree::find_min() {
    BSTNode *min = root;
    while (min->left) {
        min = min->left;
    }
    return min;
}

void BinarySearchTree::remove(int item) {
    BSTNode *node = root;
    BSTNode *prev = nullptr;
    while (node != nullptr) {
        if (node->value == item)
            break;
        prev = node;
        if (item < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (node != nullptr && node->value == item) {
        if (node == root) {
            root = remove(node);
        } else if (prev->left == node) {
            prev->left = remove(node);
        } else {
            prev->right = remove(node);
        }
    }
}

BSTNode * BinarySearchTree::remove(BSTNode *node) {
    BSTNode *new_root;
    if (node->right == nullptr) {
        new_root = node->left;
    }
    else if (node->left == nullptr) {
        new_root = node->right;
    }
    else {
        new_root = node;
        node = node->left;
        while (node->right != nullptr) {
            node = node->right;
        }
        node->right = new_root->right;
        node = new_root;
        new_root = node->left;
    }
    delete node;
    return new_root;
}

BSTNode* BinarySearchTree::get_root() {
    return root;
}

#endif