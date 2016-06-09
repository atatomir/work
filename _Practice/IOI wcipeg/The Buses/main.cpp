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

#define maxN (20 * 70)

int n, i, j, k;
vector<int> T, aux;
bool used[maxN];
bool good[maxN][maxN];

vector< pair<int, int> > work, ans;

bool valid(int t1, int t2, int pas, vector<int> &aux) {
    int dif = t2 - t1;

    if (t1 - dif >= 0) return false;
    aux.clear();

    for (t1 += dif; t1 < 60; t1 += dif) {
        while (pas < n && (used[pas] == true || T[pas] != t1)) pas++;
        if (pas == n) return false;
        aux.pb(pas++);
    }

    return true;
}

void solve(int pas) {
    int i, j;
    vector<int> loc;

    if (work.size() >= ans.size()) return;
    while (pas < n && used[pas] == true) pas++;

    if (pas == n) {
        ans = work;
        return;
    }

    // find a suitable bus route
    for (i = pas + 1; i < n; i++) {
        if (used[i]) continue;
        if (!good[pas][i]) continue;
        if (!valid(T[pas], T[i], i, loc)) continue;


        work.pb(mp(T[pas], T[i] - T[pas]));
        loc.pb(pas);
        for (auto e : loc) used[e] = true;

        solve(pas + 1);

        work.pop_back();
        for (auto e : loc) used[e] = false;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    T.resize(n);
    for (i = 0; i < n; i++) scanf("%d", &T[i]);

    sort(T.begin(), T.end());
    work.clear(); ans.resize(18);

    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            good[i][j] = valid(T[i], T[j], j, aux);

    solve(0);
    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d %d\n", e.first, e.second);

    return 0;
}
