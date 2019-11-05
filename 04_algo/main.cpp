//
//  main.cpp
//  04_algo
//
//  Created by Qmakar on 05.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//


//Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
//Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
//Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
//Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
//Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
//Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
//Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
//Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
//Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
//В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.




//4_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.


#include <iostream>
#include <random>

int pivot(int begin, int end){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(begin, end);
    int rand_int = distribution(gen);
    return rand_int;
}

int Partition(int* arr, int begin, int end, int k){
    int elem = pivot(begin, end);
    std::swap(arr[elem], arr[end]);
    int i = begin, j = begin;
    while (arr[i] < arr[end]){
        i++;
        j++;
    }
    while (j != end){
        if (arr[j] > arr[end]){
            j++;
        }
        else{
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    std::swap(arr[i], arr[j]);
    return i;
}

int main(int argc, const char * argv[]) {
    
    int n, k;
    std::cin >> n >> k;
    int arr[n];
    for (int i = 0; i < n; i++){
        std::cin >> arr[i];
    }
    
    
    int begin = 0;
    int end = n - 1;
    int p = Partition(arr, begin, end, k);
    while (k != p){
        if (k < p){
            end = p - 1;
        }
        else{
            begin = p + 1;
        }
         p = Partition(arr, begin, end, k);
    }
    
    std::cout << arr[k] << std::endl;
    
    
    return 0;
}
