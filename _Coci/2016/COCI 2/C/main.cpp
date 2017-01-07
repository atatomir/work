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

#define maxN 1000011

int n, i;
pair<int, int> act, rr;
ll v[maxN];

int act_ans;
int ans;

pair<int, int> improve(pair<int, int> ini) {
    int l, r, i, j;
    ll s1, s2;

    l = ini.first;
    r = ini.second;
    if (l >= r) return ini;

    s1 = v[l]; s2 = v[r];
    while (l < r - 1 && s1 > s2)
        s2 += v[--r];

    while (l < r && s1 != s2) {
        s1 += v[++l];
        while (l < r - 1 && s1 > s2)
            s2 += v[--r];
    }

    if (l >= r || s1 != s2) return ini;
    act_ans += (l - ini.first) + (ini.second - r);
    return mp(l + 1, r - 1);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);

    ans = n - 1;

    act = mp(1, n);
    while (true) {
        ans = min(ans, act_ans + act.second - act.first);
        rr = improve(act);
        if (act == rr || rr.first >= rr.second) {
            act = rr;
            break;
        }
        act = rr;
    }

    if (act.first >= act.second)
        ans = min(ans, act_ans);

    printf("%d", ans);


    return 0;
}
