#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1000011
#define mod 1000000007
#define inf 1000000000

struct cmp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first + a.second > b.first + b.second;
    }
};

int t, ti;
int n, i, maxi;
int to_do[maxN];

map< pair<int, int>, ll > cnt, dist;
priority_queue< pair<int, int>, vector< pair<int, int> >, cmp> Q;

ll ans;
pair<ll, ll> best;

void pre() {
    int a, b;
    pair<int, int> aux;

    cnt[mp(0, 1)] = cnt[mp(1, 0)] = 1;
    dist[mp(0, 1)] = dist[mp(1, 0)] = 1;
    Q.push(mp(0, 1));
    Q.push(mp(1, 0));

    int ccc = 0;

    while (!Q.empty()) {
        a = Q.top().first;
        b = Q.top().second;
        Q.pop();

        if (a + b + 1 > maxi) continue;

        aux = mp(a + b + 1, b);
        if (dist[aux] == 0) dist[aux] = dist[mp(a, b)] + 1, Q.push(aux);
        cnt[aux] += cnt[mp(a, b)];

        aux = mp(a, a + b + 1);
        if (dist[aux] == 0) dist[aux] = dist[mp(a, b)] + 1, Q.push(aux);
        cnt[aux] += cnt[mp(a, b)];
    }
}

void get_sol(int a, int b) {
    while (a > 0 || b > 0) {
        if (a > b) {
            printf("0 ");
            a -= b + 1;
        } else {
            printf("1 ");
            b -= a + 1;
        }
    }

    printf("\n");
}

int main()
{
    freopen("input","r",stdin);
    freopen("output","w",stdout);


    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &to_do[ti]);
        maxi = max(maxi, to_do[ti]);
    }

    pre();

    for (ti = 1; ti <= t; ti++) {
        n = to_do[ti];

        ans = 0;
        best = mp(inf, -1);

        for (i = 0; i <= n; i++) {
            int cc = cnt[mp(i, n - i)];
            if (cc == 0) continue;

            ans += cnt[mp(i, n - i)];
            ans %= mod;
            best = min(best, mp(dist[mp(i, n - i)], 1LL * i));
        }

        printf("%lld\n", ans);
        get_sol(best.second, n - best.second);
    }


    return 0;
}
