#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 50011

int n, m, i, j;
pair<int, int> P[maxN];
vector< pair<int, int> > sol;

void solve(int l, int r) {
    static pair<int, int> aux;
    if (l == r) return;

    int mid = (l + r) >> 1;
    int xx = P[mid].first;

    for (int i = l; i <= mid; i++) {
        aux = mp(xx, P[i].second);
        sol.pb(aux);
    }

    for (int i = mid + 1; i <= r; i++) {
        aux = mp(xx, P[i].second);
        sol.pb(aux);
    }

    solve(l, mid);
    solve(mid + 1, r);
}

bool is_in(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
    if (p1 > p2) swap(p1, p2);
    if (p3.first < p1.first || p3.first > p2.first) return false;

    swap(p1.first, p1.second);
    swap(p2.first, p2.second);
    swap(p3.first, p3.second);

    if (p1 > p2) swap(p1, p2);
    if (p3.first < p1.first || p3.first > p2.first) return false;

    return true;
}

int main()
{
    freopen("arbsat2.in","r",stdin);
    freopen("arbsat2.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second);
    sort(P + 1, P + n + 1);

    solve(1, n);
    sort(sol.begin(), sol.end());
    sol.resize(unique(sol.begin(), sol.end()) - sol.begin());

    int pos = 0; j = 1;
    for (i = 0; i < sol.size(); i++) {
        while (j <= n && P[j] < sol[i]) j++;
        if (P[j] != sol[i]) sol[pos++] = sol[i];
    }
    sol.resize(pos);


    printf("%d\n", sol.size());
    for (auto e : sol)
        printf("%d %d\n", e.first, e.second);

    //! checker
    /*for (i = 1; i <= n; i++) sol.pb(P[i]);
    for (auto p1 : sol) {
        for (auto p2 : sol) {
            if (p1.first == p2.first || p1.second == p2.second) continue;

            bool found = false;
            for (auto p3 : sol) {
                if (p1 == p3) continue;
                if (p2 == p3) continue;

                if (is_in(p1, p2, p3)) {
                    found = true;
                    break;
                }
            }

            if (!found) cerr << "Err\n";
        }
    }*/

    return 0;
}
