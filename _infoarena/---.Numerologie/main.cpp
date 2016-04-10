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

#define maxN 1301

int n, m, i, j, x;
vector<int> divs[maxN];
int cost[maxN];
int ans = 1301000000;

vector<int> primes;
bool used[maxN];
int act, tmp;

bool tmp_used[maxN];

void _back(int pas) {
    if (pas == primes.size()) {
        tmp = act;
        memcpy(tmp_used, used, sizeof(used));

        for (int i = 1; i <= n; i++) {
            bool good = false;
            for (int e : divs[i])
                if (tmp_used[e])
                    {good = true; break;}

            if (!good) {
                int d = divs[i].back();
                if (d * d <= m) return;

                tmp += cost[d];
                tmp_used[d] = true;
            }
        }

        ans = min(ans, tmp);

        return;
    }

    _back(pas + 1);

    act += cost[primes[pas]];
    used[primes[pas]] = true;
    _back(pas + 1);
    act -= cost[primes[pas]];
    used[primes[pas]] = false;
}

int main()
{
    freopen("numerologie.in","r",stdin);
    freopen("numerologie.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);

        for (j = 2; j * j <= x; j++) {
            if (x % j) continue;
            divs[i].pb(j);
            while (x % j == 0) x /= j;
        }

        if (x) divs[i].pb(x);
    }

    for (i = 1; i <= m; i++) {
        scanf("%d", &cost[i]);

        if (i * i <= m && cost[i] != -1) primes.pb(i);
    }

    _back(0);
    printf("%d", ans);

    return 0;
}
