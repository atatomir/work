#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 55

int n, i, j, cnt, k;
int A[maxN][maxN], B[maxN][maxN];
int go[maxN * maxN];
int help[maxN * maxN];

bool us[maxN * maxN];
vector<int> sp;
vector<int> cic;
long long found;

int _how;

void dfs(int node) {
    us[node] = true;
    cnt++;

    if (!us[go[node]])
        dfs(go[node]);
}

int gcd(int a, int b) {
    if (a < b) swap(a, b);

    while (b) {
        a %= b;
        swap(a, b);
    }

    return a;
}

void _back(int pas, int now) {
    if (pas == cic.size()) {
        if (_how != k) return;

        int how = 0;
        for (auto e : cic)
            if (now % e == 0) how += help[e];

        if (how == k) found = now;

        return;
    }

    _back(pas + 1, now);

    long long aux = 1LL * now * cic[pas];
    aux /= gcd(now, cic[pas]);

    _how += help[ cic[pas] ];
    if (aux < found) _back(pas + 1, aux);
    _how -= help[ cic[pas] ];
}

int main()
{
    freopen("spirala2.in","r",stdin);
    freopen("spirala2.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        if (i & 1)
            for (j = 1; j <= n; j++) A[i][j] = ++cnt;
        else
            for (j = n; j >= 1; j--) A[i][j] = ++cnt;
    }

    for (i = 1; 2 * i <= n; i++) {
        int ll = i;
        int dd = n - i + 1;

        for (j = ll; j < dd; j++) sp.pb(A[ll][j]);
        for (j = ll; j < dd; j++) sp.pb(A[j][dd]);
        for (j = dd; j > ll; j--) sp.pb(A[dd][j]);
        for (j = dd; j > ll; j--) sp.pb(A[j][ll]);
    }

    if (n & 1) sp.pb(A[ (n + 1) / 2 ][ (n + 1) / 2 ]);

    cnt = 0;
    for (i = 1; i <= n; i++) {
        if (i & 1)
            for (j = 1; j <= n; j++) B[i][j] = sp[cnt++];
        else
            for (j = n; j >= 1; j--) B[i][j] = sp[cnt++];
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            go[ B[i][j] ] = A[i][j];

    for (i = 1; i <= n * n; i++) {
        if (us[i]) continue;

        cnt = 0;
        dfs(i);
        cic.pb(cnt);
    }

    for (auto e : cic)
        help[e] += e;

    sort(cic.begin(), cic.end());
    cic.resize(unique(cic.begin(), cic.end()) - cic.begin());
    reverse(cic.begin(), cic.end());

    cerr << cic.size();

    found = (1LL << 31);
    _back(0, 1);

    printf("%lld", found);

    return 0;
}
