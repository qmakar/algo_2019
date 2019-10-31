//
//  main.cpp
//  01_algo
//
//  Created by qmakar on 30.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include <iostream>

class Deque {
    int* arr = nullptr;
    int size = 0;
    int head = -1;
    int tail = -1;
public:
    ~Deque();
    
    // Проверка очереди на пустоту
    bool empty() const;
    
    // Добавление элемента
    void push(int& border1, int direction, int& border2, int data);
    void push_back(int data){
        push(tail, +1, head, data);
    }
    void push_front(int data){
        push(head, -1, tail, data);
    }
    
    // Извлечение
    int pop(int& limit, int direction);
    int pop_back() {
        return pop(tail, -1);
    }
    int pop_front(){
        return pop(head, +1);
    }
    
    void print(){
        std::cout << "ht:  " << head << " " << tail << std::endl;
        for (int i = 0; i < size; i++){
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

Deque::~Deque() {
    delete[] arr;

}
void Deque::push(int& border1, int direction, int& border2, int data){
    // arr = ?
    if (arr == nullptr){
        arr = new int [1];
        arr[0] = data;
        size = 1;
        head = 0;
        tail = 0;
        return;
    }
    
    // arr = |h,t|   or  |.|  or  |.|h,t|  or  |h,t|.| or  |.|.|
    if (head == tail){
        // arr = |h,t|   or  |.|
        if (size == 1){
            // arr = |.|
            if (head == -1){
                arr[0] = data;
                head = 0;
                tail = 0;
                return;
            }
            // arr = |h,t|
            int* tmp = new int [2];
            head = 0;  // it is important. Change ptrs and then assign new values
            tail = 1;
            tmp[border1] = data;
            tmp[border2] = arr[0];
            delete [] arr;
            arr = tmp;
            size = 2;
            
            return;
        }
        // arr = |.|h,t|  or  |h,t|.|  or  |.|.|
        else{
            if (head == -1){
                arr[0] = data;
                head = 0;
                tail = 0;
                return;
            }
            border1 = (border1 + direction + size) % size;
            arr[border1] = data;
            return;
        }
    }
    
    // arr = |...|h|...|t|...|
    if (head < tail){
        if ((direction < 0 && border1 + direction >= 0) ||
            (direction > 0 && border1 + direction < size)
            ){
            border1 = border1 + direction;
            arr[border1] = data;
            return;
        }
    }
    
    // arr = |t|...|h|...|  or  |...|h|...|t|
    if ((direction < 0 && (border1 + direction + size) % size > border2) ||
        (direction > 0 && (border1 + direction + size) % size < border2)
        ){
        border1 = (border1 + direction + size) % size;
        arr[border1] = data;
        return;
    }
    
    // arr = |...|t|h|...|  or  |h|...|t|
    if ((border1 + direction + size) % size == border2){
        int* tmp = new int [size * 2];
        int j = 0;
        // if insert to begin
        if (direction < 0){
            tmp[j++] = data;
        }
        // arr = |...|t|h|...|
        if (tail < head){
            for (int i = head; i < size; i++){
                tmp[j++] = arr[i];
            }
            for (int i = 0; i <= tail; i++){
                tmp[j++] = arr[i];
            }
        }
        // arr = |h|...|t|
        else{
            for (int i = head; i <= tail; i++){
                tmp[j++] = arr[i];
            }
        }
        // if insert to end
        if (direction > 0){
            tmp[j] = data;
            tail = j;
        }
        else{
            tail = j - 1;
        }
        head = 0;
        delete [] arr;
        arr = tmp;
        size *= 2;
        return;
    }
}


int Deque::pop(int & limit, int direction){
    int res = -1;
    
    // arr = ?
    if (arr == nullptr || head == -1){
        return res;
    }
    
    res = arr[limit];
    
    // arr = |h,t|  or  |.|h,t|  or  |h,t|.|
    if (head == tail){
        head = -1;
        tail = -1;
    }
    else {
        limit = (limit + size + direction) % size;
        // arr = |...|h|...|t|...|
        if (head <= tail){
            if ((tail - head) < size / 4){ // free half of memory
                int j = 0;
                int *tmp = new int [size / 2];
                for (int i = head; i <= tail; i++){
                    tmp[j++] = arr[i];
                }
                delete [] arr;
                arr = tmp;
                head = 0;
                tail = j-1;
                size = size / 2;
            }
        }
        // arr = |...|t|...|h|...|
        else{
            if (size - head + tail + 1 < size / 4){ // free half of memory
                int j = 0;
                int *tmp = new int [size / 2];
                for (int i = head; i < size; i++){
                    tmp[j++] = arr[i];
                }
                for (int i = 0; i <= tail; i++){
                    tmp[j++] = arr[i];
                }
                delete [] arr;
                arr = tmp;
                head = 0;
                tail = j-1;
                size = size / 2;
            }
        }
    }
    return res;
}


int main(int argc, const char * argv[]) {
    int commands_count = 0;
    std::cin >> commands_count;
    
    Deque deque;
    for (int i = 0; i < commands_count; ++i) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        if (command == 1) {
            deque.push_front(value);
        }
        else if (command == 3) {
            deque.push_back(value);
        }
        else if (command == 2) {
            if (deque.pop_front() != value) {
                std::cout << "NO";
                return 0;
            }
        }
        else if (command == 4) {
             if (deque.pop_back() != value) {
                std::cout << "NO";
                return 0;
            }
        }
//        deque.print();
    }
    std::cout << "YES";
    return 0;
}
