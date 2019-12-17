//
//  main.cpp
//  11_algo
//
//  Created by Mak on 16.12.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>

typedef enum : char {
    white,
    gray,
    black,
} colors;

short bfs( short u, short N, const std::vector<short> *a){
    std::queue<int> q;
    q.push(u);
    
    std::vector<colors> visited(N, white);
    std::vector<short> parent(N, -1);
    std::vector<short> way(N, 0);
    
    parent[u] = -1;
    visited[u] = black;
    short len = 0;
    
    while (!q.empty()) {
        short v = q.front();
        q.pop();
        visited[v] = black;
        for (short i = 0; i < a[v].size(); ++i) {
            short to = a[v][i];
            if (visited[to] == white) {
                visited[to] = gray;
                q.push (to);
                parent[to] = v;
                way[to] = way[v] + 1;
            }
            else if ((visited[to] == gray) || (visited[to] == black && parent[v] != to)){
                //раскручивать
                len = way[v] + way[to] + 1;
                short from = 0;
                
                short find1 = v, find2 = parent[to];
                short tmp = to;
                while (find1 != find2 && find1 != tmp){
                    tmp = find2;
                    find1 = parent[find1];
                    find2 = parent[find2];
                }
                from = way[find1];
                len -= 2 * from;
                return len;
            }
        }
    }
    return len;
}

int main(int argc, const char * argv[]) {
    
    
    int M, N;
    std::cin >> N >> M;
    std::vector<short> a[N];
    int row, col;
    for (int i = 0; i < M; i++){
        std::cin >> row >> col;
        a[row].push_back(col);
        a[col].push_back(row);
    }
    
    
    std::queue<short> q;
    short min = N + 1;
    short len;
    for (int i = 0; i < N; i++) {
        len = bfs(i, N, a);
        if (len != 0 && len !=2){
            min = std::min(min, len);
        }
        
    }
    if (min == N + 1){
        std::cout << -1;
    }
    else{
        std::cout << min;
    }
        
    
    return 0;
}


//4 4
//0 1
//1 2
//2 3
//3 0

//6 6
//0 1
//1 2
//2 3
//3 0
//0 4
//5 4

//10 13
//9 1
//1 2
//2 3
//3 4
//4 5
//5 0
//0 9
//9 8
//8 7
//7 6
//5 6
//0 3
//5 4

//6 9
//0 5
//0 4
//0 3
//1 5
//1 4
//1 3
//2 5
//2 4
//2 3

//6 7
//0 1
//1 2
//2 3
//3 0
//0 4
//5 4
//5 0

//4 3
//0 1
//1 2
//2 0

//4 6
//0 1
//1 2
//2 3
//0 2
//1 3
//3 0

//5 10
//0 1
//1 2
//2 3
//0 2
//1 3
//3 0
//1 4
//4 2
//0 4
//4 3

//7 7
//0 1
//0 2
//2 3
//2 4
//3 6
//6 5
//4 5
