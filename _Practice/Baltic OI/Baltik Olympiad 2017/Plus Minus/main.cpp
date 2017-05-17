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
#define mod 1000000007

struct pos {
    ll x, y;
    char tp;

    bool operator<(const pos& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

ll n, m, k, i;
pos P[maxN];
ll ans;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll count_lines() {
    ll ans = 0;
    ll i, j, pp;
    ll dif = n;
    bool exist[2];

    sort(P + 1, P + k + 1);
    for (i = 1; i <= k; i = j) {
        for (j = i; j <= k; j++)
            if (P[j].x != P[i].x)
                break;

        dif--;
        exist[0] = exist[1] = false;

        for (pp = i; pp < j; pp++)
            exist[(P[pp].y & 1) ^ (P[pp].tp == '+' ? 1 : 0)] = true;

        if (exist[0] && exist[1]) return 0;
    }

    return poww(2, dif);
}

ll count_both() {
    bool exist[2];

    exist[0] = exist[1] = false;

    for (i = 1; i <= k; i++)
        exist[ (P[i].x & 1) ^ (P[i].y & 1) ^ (P[i].tp == '+' ? 1 : 0) ] = true;

    if (exist[0] && exist[1]) return 0;
    return 1;
}

int main()
{
   // freopen("test.in","r",stdin);

    cin >> n >> m >> k;
    for (i = 1; i <= k; i++)
        cin >> P[i].tp >> P[i].x >> P[i].y;


    if (k == 0) {
        ans = poww(2, n) + poww(2, m) + mod - 2;
        ans %= mod;
        cout << ans;
        return 0;
    }

    ans = count_lines();

    swap(n, m);
    for (i = 1; i <= k; i++) swap(P[i].x, P[i].y);

    ans += count_lines();
    ans += mod - count_both();

    ans %= mod;
    cout << ans;


    return 0;
}
