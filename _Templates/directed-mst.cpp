#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


struct Edge {int x, y, w;};

int dmst(int N, vector<Edge> E, int root) {
    const int inf = 1000000000;
    int answer = 0;

    vector<int> cost(N), from(N), visited(N), label(N);

    while (N > 1) {
        // init
        for (int i = 0; i < N; i++) {
            cost[i] = inf;
            visited[i] = -1;
            label[i] = -1;
            from[i] = -1;
        }

        // find best option
        for (auto e: E) {
            if (e.x == e.y) continue;
            if (cost[e.y] > e.w) {
                cost[e.y] = e.w;
                from[e.y] = e.x;
            }
        }

        // add costs
        cost[root] = 0;
        for (int i = 0; i < N; i++) {
            if (cost[i] == inf) return -1;
            answer += cost[i];
        }
        
        // find cycles
        int K = 0;
        for (int i = 0; i < N; i++) {
            int x = i;
            for (; visited[x] == -1 && x != root; x = from[x]) 
                visited[x] = i;

            if (x != root && visited[x] == i) {
                for (; label[x] == -1; x = from[x]) label[x] = K;
                K++;
            }
        }

        // no cycle found
        if (K == 0) break;

        // add labels
        for (int i = 0; i < N; i++) 
            if (label[i] == -1)
                label[i] = K++;
        
        // relabel nodes
        N = K;
        root = label[root];
        for (auto& e: E) {
            int new_x = label[e.x];
            int new_y = label[e.y];
            if (new_x != new_y) e.w -= cost[e.y];
            e.x = new_x;
            e.y = new_y;
        }
    }

    return answer;
}

int main()
{
    //freopen("test.in","r",stdin);
    return 0;
}
