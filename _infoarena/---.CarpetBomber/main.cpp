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

#define maxN 8333
#define maxT 1033

int n, i, j, t, x, y, ans;
vector< pair<int, int> > ord[maxT];

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return mp(a.first, -a.second) < mp(b.first, -b.second);
}

void modif(vector< pair<int, int> >& v) {
    int pos = 0;
    int maxi = 0;

    sort(v.begin(), v.end());
    for (auto e : v) {
        if (e.second > maxi) {
            v[pos++] = e;
            maxi = e.second;
        }
    }

    v.resize(pos);
}

int solve(vector< pair<int, int> >& v1, vector< pair<int, int> >& v2) {
    int last, can_go, p1, p2;
    int ans = 0;

    last = 0;
    can_go = 0;

    p1 = 0; p2 = 0;
    while (p1 < v1.size() || p2 < v2.size()) {
        auto act = mp(0, 0);

        if (p1 == v1.size())
            act = v2[p2++];
        else if (p2 == v2.size())
            act = v1[p1++];
        else if (v1[p1] < v2[p2])
            act = v1[p1++];
        else
            act = v2[p2++];

        if (last + 1 < act.first) {
            last = can_go;
            ans++;
        }

        if (last + 1 < act.first)
            return n + 13;

        can_go = max(can_go, act.second);
    }

    if (last != 1000000) {
        last = can_go;
        ans++;
    }

    if (last != 1000000) return n + 13;
    return ans;
}

int main()
{
    freopen("carpetbomber.in","r",stdin);
    freopen("carpetbomber.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &t, &x, &y);
        ord[t].pb(mp(x, y));
    }

    t = 1024; ans = n + 13;
    for (i = 1; i <= t; i++) {
        modif(ord[i]);
        ans = min(ans, solve(ord[i], ord[t + 1]));
    }

    for (i = 1; i <= t; i++)
        for (j = 1; j <= t; j++)
            if (i != j)
                ans = min(ans, solve(ord[i], ord[j]));

    if (ans > n)
        printf("-1");
    else
        printf("%d", ans);


    return 0;
}
