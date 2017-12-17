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

#define maxN 411

int n, q, i, j, valmax;
int s[maxN];
pair<int, int> Q[2 * maxN];

vector<int> aux;
int sum[maxN];
bool dpl[maxN][maxN * maxN];
bool dpr[maxN][maxN * maxN];
int ans[2 * maxN];

void answer_query(int id) {
    auto act = Q[id];
    vector<int> v1, v2;
    int i, p, target;
    int best = 1000000000;

    v1 = v2 = {};
    for (i = 0; i <= valmax; i++)
        if (dpl[act.first][i])
            v1.pb(i);
    for (i = 0; i <= valmax; i++)
        if (dpr[act.second][i])
            v2.pb(i);

    target = (sum[act.second] - sum[act.first - 1]) / 2;
    p = v2.size() - 1;

    for (auto e : v1) {
        while (p > 0) {
            if (e + v2[p - 1] < target) break;
            p--;
        }

        best = min(best, abs(sum[act.second] - sum[act.first - 1] - 2 * (e + v2[p])) );
        if (p != 0)
            best = min(best, abs(sum[act.second] - sum[act.first - 1] - 2 * (e + v2[p - 1])) );
    }

    ans[id] = best;
}

void solve(int l, int r, vector<int>& Q1) {
    int i, j;
    vector<int> Q2, Q3;
    int mid = (l + r) >> 1;

    if (Q1.empty()) return;

    Q2 = Q3 = {};
    for (i = 0; i < Q1.size(); i++) {
        auto act = Q[Q1[i]];

        if (act.second < mid)
            continue;

        if (act.first <= mid)
            Q2.pb(Q1[i]);
        else
            Q3.pb(Q1[i]);

        Q1[i] = Q1.back();
        Q1.pop_back();
        i--;
    }

    solve(l, mid, Q1);
    solve(mid + 1, r, Q3);

    //! compute some dps
    valmax = (r - l + 1) * maxN;
    for (i = l; i <= r; i++)
        for (j = 0; j <= valmax; j++)
            dpl[i][j] = dpr[i][j] = false;

    dpr[mid][0] = true;
    for (i = mid + 1; i <= r; i++) {
        for (j = 0; j <= valmax; j++)
            dpr[i][j] = dpr[i - 1][j];
        for (j = s[i]; j <= valmax; j++)
            dpr[i][j] |= dpr[i - 1][j - s[i]];
    }

    dpl[mid + 1][0] = true;
    for (i = mid; i >= l; i--) {
        for (j = 0; j <= valmax; j++)
            dpl[i][j] = dpl[i + 1][j];
        for (j = s[i]; j <= valmax; j++)
            dpl[i][j] |= dpl[i + 1][j - s[i]];
    }

    for (auto e : Q2)
        answer_query(e);
}

int main()
{
    freopen("armate.in","r",stdin);
    freopen("armate.out","w",stdout);

    cin >> n >> q;
    for (i = 1; i <= n; i++) cin >> s[i], sum[i] = s[i] + sum[i - 1];
    for (i = 1; i <= q; i++)
        cin >> Q[i].first >> Q[i].second, aux.pb(i);

    solve(1, n, aux);
    for (i = 1; i <= q; i++)
        cout << ans[i] << '\n';


    return 0;
}
