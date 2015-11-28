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
int lvl[maxN];


bool dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to.first]) continue;

        lvl[to.first] = lvl[node] + 1;
        dfs(to.first);

        if (lvl[node] % 2 == 0) {
            if (from[to.second] == node)
                ans[to.second] = true;
            else
                ans[to.second] = false;
        } else {
            if (from[to.second] == node)
                ans[to.second] = false;
            else
                ans[to.second] = true;
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

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
