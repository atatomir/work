#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define pii pair<int, int>

#define maxN 100011

int n, i, x, y;
vector< pii > list[maxN];
int from[maxN], to[maxN];
bool us[maxN];
int dad[maxN];

bool ans[maxN];


bool dfs(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i].first;

        if (us[to]) {
            list[node][i] = list[node][ list[node].size() -1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        dad[to] = list[node][i].second;
        if (dfs(to) == true) {
            list[node][i] = list[node][ list[node].size() -1 ];
            list[node].pop_back();
            i--;
            continue;
        }
    }

    if (list[node].empty())
        return false;

    for (auto e : list[node]) {
        int id = e.second;

        if (e.first == from[id])
            ans[id] = true;
        else
            ans[id] = false;
    }

    if (node != 1) {
        int id = dad[node];

        if (node == to[id])
            ans[id] = true;
        else
            ans[id] = false;
    }

    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &from[i], &to[i]);
        list[from[i]].pb(mp(to[i], i));
        list[to[i]].pb(mp(from[i], i));
    }

    dfs(1);

    for (i = 1; i < n; i++)
        printf( (ans[i] ? "1\n" : "0\n") );


    return 0;
}
