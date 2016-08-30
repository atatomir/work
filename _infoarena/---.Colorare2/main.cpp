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

#define maxN 111
#define maxK 2511

int n, m, k, K, i, x, y;
vector< pair<int, int> > list[maxN];
int ans[maxK], rez[maxK], ans_rez;
bool us[maxN];
int l[maxN], r[maxN];
vector<int> bulan;
int step;

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (auto to : list[node])
        if (!r[to.first])
            {l[node] = to.first; r[to.first] = node; return true;}

    for (auto to : list[node])
        if (pairUp(r[to.first]))
            {l[node] = to.first; r[to.first] = node; return true;}

    return false;
}

void pair_them(int col) {
    bool need;
    int i;

    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));

    need = true;
    while (need) {
        need = false;
        memset(us, 0, sizeof(us));

        for (int i : bulan)
            if (!l[i])
                need |= pairUp(i);
    }

    for (i = 1; i <= n; i++) {
        if (!l[i]) continue;

        k--;
        for (int j = 0; j < list[i].size(); j++) {
            if (list[i][j].first != l[i]) continue;
            ans[list[i][j].second] = col;
            list[i][j] = list[i].back();
            list[i].pop_back();
            break;
        }

    }
}

void try_with(bool ordered) {
    freopen("colorare2.in","r",stdin);

    scanf("%d%d%d", &n, &m, &k); K = k;
    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(mp(y - n, i));
    }

    bulan = {};
    for (i = 1; i <= n; i++) bulan.pb(i);
    if (!ordered) reverse(bulan.begin(), bulan.end());

    step = 1;
    while (k > 0) {
        pair_them(step);
        step++;
    }

    step--;
}

int main()
{
    freopen("colorare2.out","w",stdout);

    try_with(true);
    ans_rez = step;
    memcpy(rez, ans, sizeof(rez));

    try_with(false);
    if (step > ans_rez) {
        step = ans_rez;
        memcpy(ans, rez, sizeof(ans));
    }


    printf("%d\n", step);
    for (i = 1; i <= K; i++)
        printf("%d\n", ans[i]);

    return 0;
}
