#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 500111

#define mod 666013
#define mod2 1180903
#define base 31


int inv, inv2;
vector<int> p1, ip1;
vector<int> p2, ip2;
int _hash[maxN], _hash2[maxN];


int n, cnt, i;
char s[maxN << 1], aux[maxN << 1];
int dp[maxN << 1];

unordered_map< ll , int> H;
int ans;

int c1, c2;


int my_pow(int a, int b) {
    int ans = 1;

    while (b) {
        if (b & 1) ans = (1LL * ans * a) % mod;
        b >>= 1;
        a = (1LL * a * a) % mod;
    }

    return ans;
}

int my_pow2(int a, int b) {
    int ans = 1;

    while (b) {
        if (b & 1) ans = (1LL * ans * a) % mod2;
        b >>= 1;
        a = (1LL * a * a) % mod2;
    }

    return ans;
}

void preprocess() {
    _hash[1] = aux[1] - 'a' + 1;

    for (int i = 2; i <= n; i++)
        _hash[i] = (_hash[i - 1] + p1[i - 1] * (aux[i] - 'a' + 1)) % mod;

    //!-----------------------------

    _hash2[1] = aux[1] - 'a' + 1;

    for (int i = 2; i <= n; i++)
        _hash2[i] = (_hash2[i - 1] + p2[i - 1] * (aux[i] - 'a' + 1)) % mod2;
}

ll query(int l, int r) {
    int v1 = (1LL * (_hash[r] - _hash[l - 1] + mod) * ip1[l - 1]) % mod;
    int v2 = (1LL * (_hash2[r] - _hash2[l - 1] + mod2) * ip2[l - 1]) % mod2;
    return ((1LL * v1) << 30) + v2;
}

void solve(int id) {
    int i, l, r;
    int C, last;
    ll act_hash;

    n = strlen(aux + 1);
    cnt = 0;

    preprocess();

    //! generate new string
    s[0] = '@';
    for (i = 1; i < n; i++) {
        s[++cnt] = aux[i];
        s[++cnt] = '.';
    }
    s[++cnt] = aux[n];
    s[cnt + 1] = '#';

    C = last = 0;
    for (i = 1; i <= cnt; i++) {
        dp[i] = 1;
        if (i <= last) dp[i] = min(last - i + 1, dp[2 * C - i]);
        while (s[ i - dp[i] ] == s[ i + dp[i] ]) dp[i]++;

        if (last < i + dp[i] - 1) {
            C = i;
            last = i + dp[i] - 1;
        }

        if (i % 2) { //! odd
            l = (i + 1) / 2;
            r = l - 1 + (dp[i] + 1) / 2;
        } else { //! even
            l = (i + 1 + 1) / 2;
            r = l - 1 + dp[i] / 2;

            if (dp[i] == 1) continue;
        }

        for (; r >= l; r--) {
            act_hash = query(l, r) * (i % 2 ? -1 : 1);
            int res = H[act_hash];

            if (res & id) break;
            H[act_hash] = res | id;
            if ((res | id) == 3) {
                ans++;
                if (act_hash < 0) c1++; else c2++;
            }
        }
    }


}




int main()
{
    freopen("unicat.in","r",stdin);
    freopen("unicat.out","w",stdout);

    //!-----------------------------

    H.clear();

    p1.clear();
    p1.pb(1);
    for (i = 2; i < maxN; i++) p1.pb((p1.back() * base) % mod);

    p2.clear();
    p2.pb(1);
    for (i = 2; i < maxN; i++) p2.pb((p2.back() * base) % mod2);

    ip1.clear();
    inv = my_pow(base, mod - 2);
    ip1.pb(1);
    for (i = 2; i <= maxN; i++) ip1.pb((1LL * ip1.back() * inv) % mod);

    ip2.clear();
    inv2 = my_pow2(base, mod2 - 2);
    ip2.pb(1);
    for (i = 2; i <= maxN; i++) ip2.pb((1LL * ip2.back() * inv2) % mod2);

    //!-----------------------------


    scanf("%s\n", aux + 1);
    solve(1);

    memset(aux, 0, sizeof(aux));
    scanf("%s\n", aux + 1);
    solve(2);

    printf("%d", ans);
    cerr << c1 << ' ' << c2 << ' ' << c1 + c2 << ' ' << n;

    return 0;
}
