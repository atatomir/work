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

#define maxN 1024
#define maxK 5011

const int lim = 5001;

int n, i, x[maxN], aux;
vector<int> list[maxN];
int alt[maxN];

int ss, dd;
bool dp[2][maxK];

void dfs(int node) {
    int i;
    ll sum = 0;

    for (auto to : list[node])
        dfs(to);

    memset(dp, 0, sizeof(dp));
    ss = 0; dd = 1;
    dp[ss][0] = true;

    for (auto to : list[node]) {
        memset(dp[dd], 0, sizeof(dp[dd]));

        for (i = 0; i + alt[to] <= x[node]; i++)
            dp[dd][i + alt[to]] |= dp[ss][i];

        for (i = 0; i + x[to] <= x[node]; i++)
            dp[dd][i + x[to]] |= dp[ss][i];

        sum += alt[to] + x[to];
        swap(ss, dd);
    }

    for (i = x[node]; i >= 0; i--)
        if (dp[ss][i])
            break;

    if (i < 0) {
        cout << "IMPOSSIBLE";
        exit(0);
    }

    alt[node] = sum - i;

}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 2; i <= n; i++) {
        scanf("%d", &aux);
        list[aux].pb(i);
    }

    for (i = 1; i <= n; i++) cin >> x[i];
    dfs(1);


    cout << "POSSIBLE";

    return 0;
}
