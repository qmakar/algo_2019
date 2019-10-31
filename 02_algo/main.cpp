//
//  main.cpp
//  02_algo
//
//  Created by qmakar on 31.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include <iostream>
#include <vector>

#define MIN -1
#define MAX 1

// Очередь с приоритетом для задач 2
class PriorityQueue {
    std::vector<int> arr_;
//    int size = 0;
    int priority_;
    int last_ = -1;
public:
    PriorityQueue(int priority = MIN) : priority_(priority){};
    
    int get_last() const {return last_;}
    int pop();
    void push(int value);
    
    // 1 - good relation for PriorityQueue, 0 - bad
    int cmp_priority(int ind1, int ind2){
        return (arr_[ind1] - arr_[ind2]) * priority_;
    }
    
    void print(){
        for (int i = 0; i <= last_; i++){
            std::cout << arr_[i] << " ";
        }
        std::cout << std::endl;
    }
};

void PriorityQueue::push(int value){
    arr_.push_back(value);
    last_ += 1;
    
    int cur = last_;
    int parent = (last_ - 1) / 2;
    while (cur > 0 && arr_[parent] > arr_[cur]){
        std::swap(arr_[parent], arr_[cur]);
        cur = parent;
        parent = (parent - 1 ) / 2;
    }
}

int PriorityQueue::pop(){
    if (last_ == -1){
        return 0;
    }
    
    int result = arr_[0];
    arr_[0] = arr_[last_];
    arr_.pop_back();
    last_ -= 1;
    
    int cur = 0;
    
    while (true){
        int left_child = cur * 2 + 1;
        int right_child = cur * 2 + 2;
        
        if (left_child <= last_){
            int ind = left_child;
            if (right_child <= last_){
                if (cmp_priority(left_child, right_child) < 0){
                    ind = right_child;
                }
            }
            if (cmp_priority(ind, cur) > 0){
                std::swap(arr_[ind], arr_[cur]);
                cur = ind;
            }
            else{
                break;
            }
        }
        else{
            break;
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    PriorityQueue heap(MIN);
    
    int k;
    std::cin >> k;
    
    int num;
    for (int i = 0; i < k; i++){
        std::cin >> num;
        heap.push(num);
//        heap.print();
    }
    
    int res = 0;
    if (heap.get_last() == 0){
        res = heap.pop();
    }
    else {
        while(heap.get_last() != 0){
            int a = heap.pop();
            int b = heap.pop();
            res += a + b;
            heap.push(a + b);
        }
    }

    std::cout << res << std::endl;
    return 0;
}
