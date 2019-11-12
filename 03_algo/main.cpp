//
//  main.cpp
//  03_algo
//
//  Created by Qmakar on 02.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//

//  Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.

#include <iostream>

void merge(int* arr, int n, int left, int right, int len){
    if (left + len > n){
        len = n - left; // set len as min(step_size, rest_elements_in_array)
    }
    if (right > n){
        right = n - 1;  // right = min(right, n)
    }
    int i = left, j = right; // index of 2 merged elements
    int i_last = right, j_last = left + len; // last index
    
    int* tmp = new int [len];
    int k = 0;
    while ((i < i_last) && (j < j_last)) { // merge if possible
        if (arr[i] < arr[j]){
            tmp[k++] = arr[i++];
        }
        else{
            tmp[k++] = arr[j++];
        }
    }
    
    while (i < i_last){  // get rest elements of left half
        tmp[k++] = arr[i++];
    }
    
    while (j < j_last){  // get rest elements of right half
        tmp[k++] = arr[j++];
    }
    
    k = 0;
    for (i = left; i < left + len; i++) {  // copy to array
        arr[i] = tmp[k++];
    }
    
    delete [] tmp;
}

void merge_block(int* arr, int n, int k){
    int last = 0;
    for (int step = 2; step <= k; step *= 2) {  // for step elements inside block (step-block)
        
        for (int ind = 0; ind <= k && ind < n; ind += step) {  //  get step-block and merge
            merge(arr, n, ind, ind + step / 2, step);
            last = ind;
        }
    }
    merge(arr, n, 0, last, k); // merge rest elements of k-block
}

int main(int argc, const char * argv[]) {

    int k, n;
    std::cin >> n >> k;
    
    int len1 = std::min(n, k);
    int* first = new int [len1];
    for (int i = 0; i < len1; i++){
        std::cin >> first[i];
    }
    merge_block(first, len1, k);
    
    while (n > 0){
    
        n -= len1;
        int len2 = std::min(n, k);
        int* second = new int [len2];
        for (int i = 0; i < len2; i++){
            std::cin >> second[i];
        }
        merge_block(second, len2, k);
        
        int len = len1 + len2;
        int* total = new int [len];
        for (int i = 0; i < len1; i++){
            total[i] = first[i];
        }
        for (int i = len1; i < len; i++){
            total[i] = second[i-len1];
        }
        
        merge(total, len, 0, len1, 2*k);
        for (int j = 0; j < len1; j++) {
            std::cout << total[j] << " ";
        }
        
        delete [] first;
        
        
        first = new int [len2];
        for (int j = len1; j < len; j++) {
            first[j-len1] = total[j];
        }
        len1 = len2;
        
        delete [] total;
    }
    
    delete [] first;
    std::cout << "\n";
// merge neighbour k-blocks (all of them are sorted but it may be need to merge them pair-by-pair)
//    for (int i = 0; i < n; i += k){
//        merge(arr, n, i, i + k, 2*k);
//    }
    
//    for (int j = 0; j < len; j++) {
//        std::cout << total[j] << " ";
//    }
//    std::cout << "\n";
    
    return 0;
}

//18 5
//1  2  0  3  5
//8  9 10  4  6
//10 9 10 12 13
//12 14 11


//18 6
//1   2  0  3  8  5
//9  11  4  6 10  9
//10 12 13 12 14 11

//18 7
//1   2  0  3  8  5  9
//11  4  6 10  9 10 12
//13 12 14 11

//18 8
//1   2  0  3  8  5  9 11
//4  6  10  9 10 12 13 12
//14 11

//18 9
//1   2  0  3  8  5  9 11 4
//6  10  9 10 12 13 12 14 11

