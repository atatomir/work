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

#define maxN 100011

int n, m, i;
ll a[maxN], b[maxN];
bool us[maxN];

vector<int> act, hp;

void solve(int node) {
    int i;
    ll mini = 0;

    act.clear();
    for (; us[node] == false; node = (node + m) % n) {
        us[node] = true;
        act.pb(node);

        a[ (node + m) % n ] = a[node] + b[ (node + 1) % n ] - b[node];
        mini = min(mini, a[ (node + m) % n ]);
    }

    for (auto e : act)
        a[e] -= mini;
}

int main()
{
    freopen("criptare.in","r",stdin);
    freopen("criptare.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) scanf("%lld", &b[i]);

    for (i = 0; i < n; i++) {
        if (us[i]) continue;

        solve(i);
        if (i < m) hp = act;
    }

    ll dif = b[0];
    ll cnt = 0;

    for (i = 0; i < m; i++) dif -= a[i % n];
    for (auto e : hp)
        if (e < m % n)
            cnt++;
    dif /= cnt + (m / n) * hp.size();

    for (auto e : hp)
        a[e] += dif;

    for (i = 0; i < n; i++)
        printf("%lld ", a[i]);

    return 0;
}
