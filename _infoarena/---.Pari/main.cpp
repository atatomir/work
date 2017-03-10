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

int n, d, i, j, cnt;
int tp[maxN];
string s;

bool us[maxN];
vector<int> list[maxN];

vector< pair<int, int> > sol;


void dfs(int node, int root) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to]) continue;
        dfs(to, node);
        tp[node] ^= tp[to];
    }

    if (tp[node] && root != 0)
        sol.pb(mp(node, root));
}

int main()
{
    freopen("pari.in","r",stdin);
    freopen("pari.out","w",stdout);

    cin >> n >> d;
    for (i = 1; i <= n; i++) {
        cin >> tp[i] >> s;
        tp[i] &= 1;
        if (s[0] == 'i') tp[i] ^= 1;

        cnt += tp[i];
    }

    for (i = d; i <= n; i++) {
        if (i % 2 == 0) continue;

        for (j = i; j + i <= n; j += i) {
            list[j].pb(j + i);
            list[j + i].pb(j);
        }
    }

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        dfs(i, 0);
        if (tp[i] == 1) {
            printf("0 0 0");
            return 0;
        }
    }

    for (auto e : sol)
        printf("%d %d 1\n", e.first, e.second);


    return 0;
}
