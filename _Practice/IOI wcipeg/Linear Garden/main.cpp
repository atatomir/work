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

ll n, m, i;
ll poww[maxN];
char s[maxN];

ll ans;

int k, mini, maxi, act;
int r_mini, r_maxi, r_act;

ll get_count() {
    int fl = k / 2;
    int ce = (k + 1) / 2;

    if (maxi - mini > 2) return 0;
    if (maxi - mini == 2) {
        if (act != mini && act != maxi)
            return poww[ce] % m;
        else
            return poww[fl] % m;
    } else {
        return ( poww[ce] + poww[fl] - 1 ) % m;
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld\n%s", &n, &m, s + 1);
    poww[0] = 1;
    for (i = 1; i <= n; i++) poww[i] = (poww[i - 1] * 2) % m;

    ans = 1;
    k = n;
    mini = maxi = act = 0;

    for (i = 1, k--; i <= n; i++, k--) {
        r_mini = mini;
        r_maxi = maxi;
        r_act = act;

        act--;
        mini = min(mini, act);

        if (s[i] == 'L') continue;

        ans += get_count();
        if (ans >= m) ans -= m;

        act = r_act;
        mini = r_mini;
        maxi = r_maxi;

        act++;
        maxi = max(act, maxi);
    }

    printf("%d", ans);



    return 0;
}
