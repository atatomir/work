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

#define maxN 3011

int n, m, x, y, i, j;
bool adj[maxN][maxN];
bool dead[maxN];
vector<int> ans;

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> m;
    for (i = 1; i <= m; i++) {
        cin >> x >> y;
        adj[x][y] = adj[y][x] = 1;
    }

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (dead[i]) continue;
            if (dead[j]) continue;
            if (adj[i][j]) continue;

            dead[i] = dead[j] = true;
        }
    }

    for (i = 1; i <= n; i++)
        if (!dead[i])
            ans.pb(i);

    ans.resize(n / 3);
    sort(ans.begin(), ans.end());
    for (i = 0; i < ans.size(); i++)
        cout << ans[i] << ' ';


    return 0;
}
