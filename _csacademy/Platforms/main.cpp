#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define inf 1000000000
#define ll long long
#define pii pair<int, int>


int n, i, m;
pair<int, int> Plat[maxN];
int Ball[maxN];

int ans[maxN];
ll sol;

vector< pii > aux;

int s_dim;
pii S[maxN];

int cb(int x) {
    int ans = 0;

    for (int step = 1 << 20; step; step >>= 1)
        if (ans + step <= s_dim)
            if (S[ans + step].first >= x)
                ans += step;

    return ans;
}

void solve() {
    int i, j;

    aux.clear();
    s_dim = 0;

    sort(Ball + 1, Ball + m + 1);
    for (i = 2; i <= m; i++)
        aux.pb( mp(Ball[i], -i) );
    for (i = 1; i <= n; i++)
        aux.pb( mp(Plat[i].second, i) );

    sort(aux.begin(), aux.end());
    for (auto event : aux) {
        int id = event.second;

        if (id < 0) { //! add hole
            id = -id;

            int pos = Ball[id];
            int dim = pos - Ball[id - 1];

            while (s_dim > 0 && S[s_dim].first <= dim) s_dim--;
            S[++s_dim] = mp(dim, pos);
        } else { //! query platform
            int pos = Plat[id].second;
            int dim = pos - Plat[id].first;

            int where = cb(dim);
            if (where > 0)
                ans[id] = min(ans[id], pos - S[where].second);
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &Plat[i].first, &Plat[i].second);
        ans[i] = inf;
    }
    for (i = 1; i <= m; i++)
        scanf("%d", &Ball[i]);
    Ball[++m] = -inf; Ball[++m] = inf;

    //! left -> right
    solve();

    for (i = 1; i <= n; i++) {
        Plat[i].first = -Plat[i].first;
        Plat[i].second = -Plat[i].second;

        swap(Plat[i].first, Plat[i].second);
    }
    for (i = 1; i <= m; i++)
        Ball[i] = -Ball[i];

    //! right -> left
    solve();

    sol = 0;
    for (i = 1; i <= n; i++)
        sol += ans[i];

    printf("%lld", sol);

    return 0;
}
