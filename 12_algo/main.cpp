//
//  main.cpp
//  12_algo
//
//  Created by Mak on 16.12.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>

void dfs (int v, int edge, int count, std::vector<std::pair <int,int>>* a,
                                    std::vector<bool>& used,
                                    std::vector<int>& tin,
                                    std::vector<int>& fup,
                                    std::vector<int>& result
          ) {
    used[v] = true;
    tin[v] = fup[v] = count++;
    for (int i = 0; i < a[v].size(); i++) {
        int to = a[v][i].first;
        if (a[v][i].second == edge)  continue;
        if (used[to]){
            fup[v] = std::min(fup[v], tin[to]);
        }
        else {
            dfs (to, a[v][i].second, count, a, used, tin, fup, result);
            fup[v] = std::min(fup[v], fup[to]);
            if (fup[to] > tin[v]){
                result.push_back(a[v][i].second);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    std::fstream infile;
    infile.open("/Users/mak/Documents/Programming/MADE/Algo/algo_2019/12_algo/bridges.in", std::ios_base::in);
//    if (!infile)
//    {
//        std::cout << "\nError opening file.\n";
//        return 13;
//    }

    int n, m;
    infile >> n >> m;
    std::vector<std::pair <int,int>> a[n];
    int row, col;
    for (int i = 0; i < m; i++){
        infile >> row >> col;
        a[row-1].push_back(std::make_pair(col-1, i+1));
        a[col-1].push_back(std::make_pair(row-1, i+1));
    }
    
    infile.close();
    std::vector<bool> used(n, false);
    std::vector<int> tin(n, 0);
    std::vector<int> fup(n, 0);
    std::vector<int> result;
    
    int count = 0;
    for (int i = 0; i < n; ++i){
        if (!used[i]){
            dfs (i, -1, count, a, used, tin, fup, result);
        }
    }
    
    std::sort(result.begin(), result.end());
    
    std::fstream outfile;
    outfile.open("/Users/mak/Documents/Programming/MADE/Algo/algo_2019/12_algo/bridges.out", std::ios_base::out);
    outfile << result.size() << '\n';
    
    for (int i = 0; i < result.size(); ++i){
        outfile << result[i] << '\n';
    }
    outfile.close();
    return 0;
}


//6 7
//1 2
//2 3
//3 4
//1 3
//4 5
//4 6
//5 6
