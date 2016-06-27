/*
 *  50 points
 */

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

#define maxN 200011

int t, ti;
int n, m, cnt, i, req, no;

pair<ll, ll> ln[maxN], co[maxN];
vector<ll> E;

bool check() {
    int i, p1, p2;
    ll need, act, a_need, a_act;


    sort(ln + 1, ln + n + 1);
    reverse(ln + 1, ln + n + 1);

    sort(co + 1, co + m + 1);

    for (i = 1; i <= n; i++) swap(ln[i].first, ln[i].second);
    for (i = 2; i <= n; i++) ln[i].first += ln[i - 1].first;

    for (i = m - 1; i >= 1; i--) co[i].second += co[i + 1].second;

    E.clear();

    E.pb(1);
    for (i = 1; i <= n; i++) {E.pb(ln[i].first); E.pb(ln[i].first + 1);}
    for (i = 1; i <= m; i++) {E.pb(co[i].first); E.pb(co[i].first + 1);}

    sort(E.begin(), E.end());
    E.resize(unique(E.begin(), E.end()) - E.begin());

    need = act = 0;
    p1 = p2 = 1;
    while (co[p2].first == 0 && p2 <= m) p2++;

    for (int ie = 0; ie < E.size(); ie++) {
        int e = E[ie];

        while (ln[p1].first < e && p1 <= n) {
            need += (ln[p1].first - ln[p1 - 1].first) * ln[p1].second;
            p1++;
        }

        while (co[p2].first < e && p2 <= m) {
            act += (co[p2].first - co[p2 - 1].first) * co[p2].second;
            p2++;
        }

        a_need = need;
        a_act = act;

        if (p1 <= n) a_need += (e - ln[p1 - 1].first) * ln[p1].second;
        if (p2 <= m) a_act += (e - co[p2 - 1].first) * co[p2].second;

        if (a_need > a_act) return false;
    }

    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%lld%lld", &req, &no);
            ln[i] = mp(req, no);
        }

        scanf("%d", &m);
        for (i = 1; i <= m; i++) {
            scanf("%lld%lld", &req, &no);
            co[i] = mp(req, no);
        }

        if (check())
            printf("1\n");
        else
            printf("0\n");
    }


    return 0;
}
