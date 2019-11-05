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


int main(int argc, const char * argv[]) {

    int k, n;
    std::cin >> n >> k;
    
    int arr[n];
    for (int i = 0; i < n; i++){
        std::cin >> arr[i];
    }
    
// merge blocks per k elements
    int last = 0;
    for (int j = 0; j < n; j += k) { // for k-element blocks (k-block)
        last = j;
        for (int step = 2; step <= k; step *= 2) {  // for step elements inside block (step-block)
            
            for (int ind = j; ind <= j + k && ind < n; ind += step) {  //  get step-block and merge
                merge(arr, n, ind, ind + step / 2, step);
                last = ind;
            }
        }
        merge(arr, n, j, last, k); // merge rest elements of k-block
    }
    

// merge neighbour k-blocks (all of them are sorted but it may be need to merge them pair-by-pair)
    for (int i = 0; i < n; i += k){
        merge(arr, n, i, i + k, 2*k);
    }
    
    for (int j = 0; j < n; j++) {
        std::cout << arr[j] << " ";
    }
    
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

