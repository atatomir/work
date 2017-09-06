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

#define maxN 2024

ll a, b, l, r, n, i, dim;
int s[maxN];
bool any[maxN];

int pr[maxN], u, best;

void move_comp() {
    int i, j, need;

    for (i = 0; i < 26; i++) any[i] = false;
    for (i = 0; i < a; i++) any[s[n - i]] = true;

    need = a;
    for (i = 0; need > 0; i++) {
        if (any[i]) continue;
        need--;
        s[++n] = i;
    }
}

pair<int, int> get_data(int pos) {
    if (pos % dim == 0) {
        return mp(pos / dim, dim);
    } else {
        return mp((pos / dim) + 1, pos % dim);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> a >> b >> l >> r;

    for (i = 0; i < a; i++) s[++n] = i;
    while (n < 1000) {
        for (i = 1; i <= b; i++) s[n + i] = s[n];
        n += b;

        move_comp();
    }

    for (i = 2; i <= n; i++) {
        while (u != 0 && s[u + 1] != s[i]) u = pr[u];
        if (s[u + 1] == s[i]) u++;
        pr[i] = u;

        if ( i % (i - pr[i]) == 0 ) best = i;
    }

    dim = best - pr[best];
    cerr << dim << ' ' << best << '\n';
    //for (i = 1; i <= dim; i++) cerr << s[i] << ' '; cerr << '\n';
    //for (i = 1; i <= dim; i++) cerr << s[dim + i] << ' '; cerr << '\n';

    auto p1 = get_data(l);
    auto p2 = get_data(r);
    for (i = 0; i < 26; i++) any[i] = 0;

    if (p1.first + 1 < p2.first)
        for (i = 1; i <= dim; i++)
            any[s[i]] = true;

    if (p1.first == p2.first) {
        for (i = p1.second; i <= p2.second; i++)
            any[s[i]] = true;
    } else {
        for (i = p1.second; i <= dim; i++)
            any[s[i]] = true;
        for (i = 1; i <= p2.second; i++)
            any[s[i]] = true;
    }

    int ans = 0;
    for (i = 0; i < 26; i++)
        if (any[i])
            ans++;

    printf("%d", ans);

    return 0;
}
