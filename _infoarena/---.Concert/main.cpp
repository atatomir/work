#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 3024
#define ll long long
#define inf 1000000000000000000LL

struct intr {
    int a, b;
    int pay_a, pay_b, win;

    void read() {
        scanf("%d%d%d%d%d", &a, &b, &win, &pay_a, &pay_b);
    }

    bool operator<(const intr& who)const {
        return a < who.a;
    }
};

int n, i, j, k;
intr v[maxN];
vector<int> ev;
ll dp[maxN];
map<int, int> M;


int main()
{
    freopen("concert.in","r",stdin);
    freopen("concert.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        v[i].read();
        ev.pb(v[i].a);
        ev.pb(v[i].b);
    }

    sort(v + 1, v + n + 1);

    sort(ev.begin(), ev.end());
    ev.resize( unique(ev.begin(), ev.end()) - ev.begin() );

    for (i = 0; i < ev.size(); i++)
        M[ ev[i] ] = i;

    for (i = 1; i <= n; i++) {
        int st = M[v[i].a];
        int en = M[v[i].b];

        //! compute dp[en]
        dp[en] = max(dp[en - 1], dp[st] + 1LL * v[i].win * (v[i].b - v[i].a));
        for (j = st + 1; j < en; j++)
            dp[en] = max(dp[en], dp[j] + 1LL * v[i].win * (v[i].b - ev[j]) - v[i].pay_a);

        //! compute other values according to dp[en]
        for (j = 0; j < en; j++)
            dp[j] = max(dp[j], dp[en] - v[i].pay_b - 1LL * v[i].win * (v[i].b - ev[j]));
    }

    printf("%lld", dp[ ev.size() - 1 ]);

    return 0;
}
