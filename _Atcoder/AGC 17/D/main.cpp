#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int n, i, x, y;
int sg[maxN];
vector<int> list[maxN];

void dfs(int node, int root) {
    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);
        sg[node] ^= 1 + sg[to];
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);
    if (sg[1])
        printf("Alice");
    else
        printf("Bob");


    return 0;
}
