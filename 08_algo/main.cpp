//
//  main.cpp
//  08_algo
//
//  Created by Qmakar on 22.11.2019.
//  Copyright © 2019 Qmakar. All rights reserved.
//
//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
//Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
//1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
//g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
//Формат входных данных
//Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
//Тип операции  – один из трех символов:
//+  означает добавление данной строки в множество;
//-  означает удаление  строки из множества;
//?  означает проверку принадлежности данной строки множеству.
//При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
//Формат выходных данных
//Программа должна вывести для каждой операции одну из двух строк OK или FAIL.
//Для операции '?': OK, если элемент присутствует во множестве. FAIL иначе.
//Для операции '+': FAIL, если добавляемый элемент уже присутствует во множестве и потому не может быть добавлен. OK иначе.
//Для операции '-': OK, если элемент присутствовал во множестве и успешно удален. FAIL иначе.



#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

// big good prime number
const int a = 27644437;

// Gorner scheme
size_t Hash(const std::string& key, size_t size )
{
    size_t hash = 0;
    for (auto sym: key)
        hash = ( hash * a + sym ) % size;
    return hash;
}


size_t Probing(size_t from, size_t iter, size_t size){
    return (from + iter) % size;
}


class HashTable {
    struct HashTableNode {
        std::string key;
        
        HashTableNode(std::string key_) : key(std::move(key_)) {}
    };
    
    size_t size = 0;
    size_t count_elems = 0;
    std::vector<HashTableNode*> table;
    
    // it is flag for SEARCH
    std::vector<bool> deleted;
    
public:
    explicit HashTable(size_t initial_size);
    ~HashTable();
    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;
    
    bool Has(const std::string& key, size_t& pos) const;
    bool Add(const std::string& key);
    bool Remove(const std::string& key);
    void Rehash(size_t new_size);
    
    void Print() const;
    
};

HashTable::HashTable(size_t initial_size) : size(initial_size) {
    table = std::vector<HashTableNode*>(initial_size);
    deleted = std::vector<bool>(initial_size);
    
}

HashTable::~HashTable() {
    for (auto elem : table) {
        if (elem) {
            delete elem;
        }
    }
}

void HashTable::Rehash(size_t new_size){
    std::vector<HashTableNode*> last_table = table;
    std::fill(table.begin(), table.end(), nullptr);
    table.resize(new_size, nullptr);
    
    for (size_t i = 0; i < size; i++){
        if (last_table[i]) {
            size_t hash = Hash(last_table[i]->key, new_size);
            size_t j = 0;
            
            // if place it taken go to the next
            while ((table[hash])){
                hash = Probing(hash, j++, new_size);
            }
            table[hash] = last_table[i];
        }
    }
    size = new_size;
    
    // all elements were not deleted
    std::fill(deleted.begin(), deleted.end(), false);
    deleted.resize(new_size, false);
}

bool HashTable::Has(const std::string& key, size_t& pos) const {
    assert(!key.empty());
    
    bool was = false;
    size_t hash = Hash(key, size);
    pos = hash;
    size_t i = 0;
    
    // go to the next position
    while ((((table[hash]) &&
             (table[hash]->key != key)) ||
            ((!table[hash] &&
              (deleted)[hash])))
           && i < size){
        
        hash = Probing(hash, i++, size);
        
        // should remember first empty position to insert element
        if (!table[hash] && !was){
            pos = hash;
            was = true;
        }
    }
    
    // check if last iteration was good
    if (!table[hash] || ((i >= size) && (table[hash]->key != key))) {
        if (!was) pos = hash;
        return false;
    }
    return true;
}


void HashTable::Print() const{
    for (auto elem: table){
        if (elem){
            std::cout << elem->key << " ";
        }
        else{
            std::cout << "0 ";
        }
    }
    std::cout << std::endl;
}


bool HashTable::Add(const std::string& key) {
    assert(!key.empty());
    size_t pos = 0;
    
    // check if exist
    if (Has(key, pos)){
        return false;
    }
    
    // insert to the table
    if (!table[pos]) {
        table[pos] = new HashTableNode(key);
        count_elems++;
        
        if (1.0 * count_elems / size > 0.75){
            Rehash(size * 2);
        }
        return true;
    }
    
    return false;
}

bool HashTable::Remove(const std::string& key) {
    assert(!key.empty());
    
    size_t hash = Hash(key, size);
    size_t i = 0;
    
    // go to the next position
    while ((((table[hash]) &&
             (table[hash]->key != key)) ||
            ((!table[hash] &&
              deleted[hash]))) &&
           i < size){
        
        hash = Probing(hash, i++, size);
        
    }
    
    // check if last iteration was good
    if ( !table[hash] || ((i >= size) && (table[hash]->key != key))) {
        return false;
    }
    
    // delete element from table
    delete table[hash];
    table[hash] = nullptr;
    deleted[hash] = true;
    count_elems--;
    
    if (4 * count_elems <=  size){
        Rehash(size / 2);
    }
    
    return true;
}

int main() {
    HashTable table(8);
    char command = ' ';
    std::string value;
    size_t pos = 0;
    
    while (std::cin >> command >> value) {
        switch (command) {
            case '?':
                std::cout << (table.Has(value, pos) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
                //                table.Print();
                break;
            case '-':
                std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
                //                table.Print();
                break;
        }
    }
    return 0;
}
