//
//  main.cpp
//  07_algo
//
//  Created by Qmakar on 18.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//
//Множество натуральных чисел постоянно меняется. Элементы в нем добавляются и удаляются по одному. Вычислите указанные порядковые статистики после каждого добавления или удаления.
//Требуемая скорость выполнения запроса - O(log n) амортизированно.
//В реализации используйте сплей-деревья.
//Формат ввода
//Дано число N и N строк. (1 ≤ N ≤ 10000)
//Каждая строка содержит команду добавления или удаления натуральных чисел (от 1 до 109), а также запрос на получение k-ой порядковой статистики (0 ≤ k < N).
//Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”.
//Формат вывода
//N строк. В каждой строке - текущая k-ая порядковая статистика из запроса.


#include <iostream>

struct SplayTreeNode {
    explicit SplayTreeNode(int _value) : value(_value) {}
    
    int value = 0;
    int all_elems = 1;
    SplayTreeNode* parent = nullptr;
    SplayTreeNode* left = nullptr;
    SplayTreeNode* right = nullptr;
};

class SplayTree {
    SplayTreeNode* root = nullptr;
    
    void DeleteSubtree(SplayTreeNode* node);
    void PrintSubtree(SplayTreeNode* node) const;
    SplayTreeNode*  RotateRight(SplayTreeNode* root);
    SplayTreeNode*  RotateLeft(SplayTreeNode* root);
    
//    SplayTreeNode* RotateRight(SplayTreeNode* root);
//    SplayTreeNode* RotateLeft(SplayTreeNode* root);
    
    SplayTreeNode* Find(SplayTreeNode* from, int value);
    
    void Splay(SplayTreeNode*& root, int value);
    
public:
    ~SplayTree();
    
    void Print() const;
    void Add(int value);
    void Delete(int value);
    
    
    int k_statistics(int k);
    int k_statistics(int k, SplayTreeNode* node);
};

SplayTree::~SplayTree() {
    DeleteSubtree(root);
}

void SplayTree::DeleteSubtree(SplayTreeNode* node) {
    if (!node) return;
    DeleteSubtree(node->left);
    DeleteSubtree(node->right);
    delete node;
}
void SplayTree::Print() const {
    PrintSubtree(root);
}

void SplayTree::PrintSubtree(SplayTreeNode* node) const {
    if (!node) return;
    PrintSubtree(node->left);
    PrintSubtree(node->right);
    std::cout << node->value << ": ";
    std::cout << node->all_elems << "\n";
}

void SplayTree::Add(int value) {
    if (!root) {
        root = new SplayTreeNode(value);
        return;
    }
    
    SplayTreeNode* cur = root;
    while(true){
        if (value < cur->value && cur->left != nullptr){
            cur->all_elems++;
            cur = cur->left;
        }
        else if (value > cur->value && cur->right != nullptr){
            cur->all_elems++;
            cur = cur->right;
        }
        else{
            break;
        }
    }
    
    cur->all_elems++;
    if (value > cur->value){
        cur->right = new SplayTreeNode(value);
        cur->right->parent = cur;
    }
    else{
        cur->left = new SplayTreeNode(value);
        cur->left->parent = cur;
    }
    
    Splay(root, value);
}

void SplayTree::Delete(int value) {
    if (!root) {
//        root = new SplayTreeNode(value);
        return;
    }
    
    Splay(root, value);
    
    SplayTreeNode* new_root = root;
    if (root->left){
        new_root = new_root->left;
    
        while (new_root->right){
            new_root = new_root->right;
        }
    
        root->left->parent = nullptr;
        Splay(root->left, new_root->value);
        if(root->right){
            new_root->right = root->right;
            new_root->right->parent = new_root;
            new_root->all_elems += root->right->all_elems;
        }
    }
    else{
        new_root = root->right;
    }
    
    new_root->parent = nullptr;
    
    delete root;
    root = new_root;
}

SplayTreeNode* SplayTree::RotateRight(SplayTreeNode* root) {
    if (!root) {
        return root;
    }
    if (!root->left) {
        return root;
    }
    SplayTreeNode* new_root = root->left;
    new_root->all_elems = root->all_elems;
    root->left = new_root->right;
    if (root->left && root->left->parent){
        root->left->parent = root;
    }
    root->all_elems = 1;
    
    if (root->left){
        root->all_elems += root->left->all_elems;
    }
    if (root->right){
        root->all_elems += root->right->all_elems;
    }
    new_root->right = root;
    
    SplayTreeNode* const new_parent = root->parent;
    root->parent = new_root;
//    new_root->parent = new_parent;
    
    root = new_root;
    root->parent = new_parent;
    return root;
}

SplayTreeNode* SplayTree::RotateLeft(SplayTreeNode* root) {
    if (!root) {
        return root;
    }
    if (!root->right) {
        return root;
    }
    SplayTreeNode* new_root = root->right;
    new_root->all_elems = root->all_elems;
    root->right = new_root->left;
    if (root->right && root->right->parent){
        root->right->parent = root;
    }
    root->all_elems = 1;
    
    if (root->left){
        root->all_elems += root->left->all_elems;
    }
    if (root->right){
        root->all_elems += root->right->all_elems;
    }
    new_root->left = root;
    
    SplayTreeNode* const new_parent = root->parent;
    root->parent = new_root;
    //    new_root->parent = new_parent;
    
    root = new_root;
    root->parent = new_parent;
    return root;
}

SplayTreeNode* SplayTree::Find(SplayTreeNode* from, int value) {
    if (!from) {
        return nullptr;
    }
    
    SplayTreeNode* cur = from;
    while(cur){
        if (value < cur->value){
            cur = cur->left;
        }
        else if (value > cur->value){
            cur = cur->right;
        }
        else{
            break;
        }
    }
    
    return cur;
}

void SplayTree::Splay(SplayTreeNode*& node, int x) {
    if (!node){
        return;
    }
    
    SplayTreeNode* found_elem = Find(node, x);
    while (found_elem->parent){
        SplayTreeNode*& parent = found_elem->parent;
        if(parent == node){
            if (x < parent->value){
                found_elem = RotateRight(parent);
            }
            else{
                found_elem = RotateLeft(parent);
            }
//            return;
        }
        else{
            bool cur_left = false, par_left = false;
            if (found_elem->value < parent->value){
                cur_left = true;
            }
            if (parent->value < parent->parent->value){
                par_left = true;
            }
            if (cur_left && par_left){
                parent = RotateRight(parent->parent);
                found_elem = RotateRight(parent);
//                if (found_elem->parent){
//                    found_elem->parent->left = found_elem;
//                }
            }
            else if (!cur_left && !par_left){
                parent = RotateLeft(parent->parent);
                found_elem = RotateLeft(parent);
//                if (found_elem->parent){
//                    found_elem->parent->right = found_elem;
//                }
            }
            else if (cur_left && !par_left){
                found_elem = RotateRight(parent);
                found_elem->parent->right = found_elem;
                found_elem = RotateLeft(found_elem->parent);
//                if (found_elem->parent && found_elem->parent->value < found_elem->value){
//                    found_elem->parent->right = found_elem;
//                }
//                else if (found_elem->parent && found_elem->parent->value > found_elem->value){
//                    found_elem->parent->left = found_elem;
//                }
            }
            else{
                found_elem = RotateLeft(parent);
                found_elem->parent->left = found_elem;
                found_elem = RotateRight(found_elem->parent);
//                if (found_elem->parent && found_elem->parent->value < found_elem->value){
//                    found_elem->parent->right = found_elem;
//                }
//                else if (found_elem->parent && found_elem->parent->value > found_elem->value){
//                    found_elem->parent->left = found_elem;
//                }
            }
            if (found_elem->parent && found_elem->parent->value < found_elem->value){
                found_elem->parent->right = found_elem;
            }
            else if (found_elem->parent && found_elem->parent->value > found_elem->value){
                found_elem->parent->left = found_elem;
            }
        }
        
        
        
//        if ((x < node->value) && (node->left) && (x > node->left->value)){
//            node->left = RotateLeft(node->left);
//            node = RotateRight(node);
//        }
//        else if ((x > node->value) && (node->right) && (x > node->right->value)){
//            node->right = RotateRight(node->right);
//            node = RotateLeft(node);
//        }
//        else if (x < node->value){
//            node = RotateRight(node);
//        }
//        else{
//            node = RotateLeft(node);
//        }
    }
    node = found_elem;
}

int SplayTree::k_statistics(int k){
    return k_statistics(k, root);
}
int SplayTree::k_statistics(int k, SplayTreeNode* node){
    if (!node) {
        return -1;
    }
    
    if (node->left){
        if (node->left->all_elems == k){
            int x = node->value;
            Splay(root, x);
            return x;
        }
        if (k < node->left->all_elems){
            return k_statistics(k, node->left);
        }
        k -= node->left->all_elems;
    }
    
    if (k == 0){
        int x = node->value;
        Splay(root, x);
        return x;
    }
    
    k -= 1;
    
    if (node->right){
        return k_statistics(k, node->right);
    }
    
    int x = node->value;
    Splay(root, x);
    return x;
}


int main(int argc, const char * argv[]) {
    
    int n, A, k;
    std::cin >> n;
    
    SplayTree SplayTree;
    for (int i = 0; i < n; i++){
        std::cin >> A >> k;
        if (A > 0){
            SplayTree.Add(abs(A));
            std::cout << SplayTree.k_statistics(k) << " ";
        }
        else{
            SplayTree.Delete(abs(A));
            std::cout << SplayTree.k_statistics(k) << " ";
        }
    }
    
    return 0;
}
