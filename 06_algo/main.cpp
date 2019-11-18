//
//  main.cpp
//  06_algo
//
//  Created by Qmakar on 18.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

#include <iostream>
#include <random>

// Узел бинарного дерева
struct TreeNode {
    explicit TreeNode(int _value) : value(_value) {}
    
    int value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

class Tree {
public:
    ~Tree();
    
    void Print() const;
    
    void Add(int value);
    
private:
    TreeNode* root = nullptr;
    
    void print_subtree(TreeNode* node) const;
    
    void delete_subtree(TreeNode* node);
};

Tree::~Tree() {
    delete_subtree(root);
}

void Tree::delete_subtree(TreeNode* node) {
    if (!node) return;
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}

void Tree::Print() const {
    print_subtree(root);
}

void Tree::print_subtree(TreeNode* node) const {
    if (!node) return;
    print_subtree(node->left);
    print_subtree(node->right);
    std::cout << node->value << " ";
    
}

void Tree::Add(int value) {
    if (!root) {
        root = new TreeNode(value);
        return;
    }
    
    TreeNode* cur = root;
//    TreeNode* parent = root;
    while(true){
        if (value < cur->value && cur->left != nullptr){
//            parent = cur;
            cur = cur->left;
        }
        else if (value > cur->value && cur->right != nullptr){
//            parent = cur;
            cur = cur->right;
        }
        else{
            break;
        }
    }
    
    if (value > cur->value){
        cur->right = new TreeNode(value);
    }
    else{
        cur->left = new TreeNode(value);
    }
}


int main(int argc, const char * argv[]) {
    
    int n, elem;
    std::cin >> n;
    
    Tree tree;
    for (int i = 0; i < n; i++){
        std::cin >> elem;
        tree.Add(elem);
    }
    
    tree.Print();
    return 0;
}
