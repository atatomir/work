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

int n, m, i, j, x, y, cnt;
int a[maxN];
bool us[maxN];
vector<int> list[maxN];
vector<int> aux, rez;
ll ans;

void dfs(int node) {
    us[node] = true;
    aux.pb(a[node]);

    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> m;
    for (i = 1; i <= n; i++) cin >> a[i];
    for (i = 1; i <= m; i++) {
        cin >> x >> y;
        x++; y++;
        list[x].pb(y);
        list[y].pb(x);
    }

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        aux.clear();
        dfs(i);

        cnt++;
        sort(aux.begin(), aux.end());
        ans += aux[0];
        for (j = 1; j < aux.size(); j++) rez.pb(aux[j]);
    }

    if (cnt == 1) {
        cout << 0;
        return 0;
    }

    sort(rez.begin(), rez.end());

    if (rez.size() < cnt - 2) {
        cout << "Impossible";
        return 0;
    }

    for (i = 0; i < cnt - 2; i++)
        ans += rez[i];

    cout << ans;


    return 0;
}
