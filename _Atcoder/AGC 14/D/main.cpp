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
vector<int> list[maxN];
bool down[maxN];

void First() {
    cout << "First";
    exit(0);
}

void Second() {
    cout << "Second";
    exit(0);
}

void dfs(int node, int root) {
    int cnt = 0;

    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);
        cnt += down[to];
    }

    if (cnt >= 2) First();
    down[node] = 1 ^ cnt;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i < n; i++) cin >> x >> y, list[x].pb(y), list[y].pb(x);

    if (n % 2 == 1)
        First();

    dfs(1, 0);
    Second();

    return 0;
}
