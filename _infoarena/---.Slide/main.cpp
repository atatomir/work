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

#define maxN 2000011

int n, i;
char s[maxN];
ll t1[maxN], t2[maxN];
ll ans;

int hp[maxN], last[maxN], nxt[maxN];
ll sz[maxN], sum[maxN], sum2[maxN];

void solve(ll *to) {
    ll i, j, k, pos, ini, need, cnt;

    s[++n] = '.';

    pos = 0;
    for (i = 1; i <= n; i = j) {
        for (j = i; j <= n && s[i] == s[j]; j++);

        if (s[i] == '.') {
            sz[++pos] = j - i;
            sum[pos] = sum[pos - 1] + sz[pos];
            sum2[pos] = sum2[pos - 1] + sum[pos];
            for (k = i; k < j; k++) last[k] = pos;
        } else {
            if ( (s[i] == '@' && s[i - 1] == '#') ||
                 (s[i] == '#' && s[i - 1] == '@') ) {

                sz[++pos] = 0;
                sum[pos] = sum[pos - 1] + sz[pos];
                sum2[pos] = sum2[pos - 1] + sum[pos];
            }

            for (k = i; k < j; k++) hp[k] = k - i + 1, last[k] = pos;
        }
    }

    cnt = pos;
    pos = 0;
    sum[cnt] = 10000000;

    nxt[cnt] = cnt;
    for (i = cnt - 1; i > 0; i--) {
        if (sz[i] > 0)
            nxt[i] = i;
        else
            nxt[i] = nxt[i + 1];
    }

    n--;

    for (i = 1; i <= n; i++) {
        if (s[i] != s[i - 1]) pos = 0;

        if (s[i] == '.') {
            to[i] = 0;
        } else {
            ini = last[i];
            pos = max(pos, ini);
            need = hp[i];

            while (pos + 1 <= cnt && sum[pos + 1] - sum[ini] <= need) pos = max(pos + 1, 1LL * nxt[pos + 1] - 1);
            to[i] = (pos - ini + 1) * need;
            to[i] -= (sum2[pos] - sum2[ini]) - (pos - ini) * sum[ini];
        }
    }


}

int main()
{
    freopen("slide.in","r",stdin);
    freopen("slide.out","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    solve(t1);
    reverse(s + 1, s + n + 1);
    solve(t2);
    reverse(t2 + 1, t2 + n + 1);

    for (i = 1; i <= n; i++) ans += 1LL * min(t1[i], t2[i]);
    printf("%lld", ans);

    //for (i = 1; i <= n; i++) cerr << min(t1[i], t2[i]) << ' ';

    return 0;
}
