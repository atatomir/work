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

const int maxN = 100011;

int n, m, i, x, y, ans;
int p[maxN];
vector<int> list[maxN];
bool us[maxN];
vector<int> aux;

void dfs(int node) {
    us[node] = true;
    aux.pb(node);
    aux.pb(p[node]);
    for (auto e : list[node])
        if (!us[e])
            dfs(e);
}

int main()
{
    freopen("test.in","r",stdin);
    
    cin >> n >> m;
    for (i = 1; i <= n; i++) cin >> p[i];
    for (i = 1; i <= m; i++) {
        cin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        aux.clear();
        dfs(i);

        int bef = aux.size();

        sort(aux.begin(), aux.end());
        aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
        int aft = aux.size();
    

        ans += bef - aft;
    }

    cout << ans;




    return 0;
}
