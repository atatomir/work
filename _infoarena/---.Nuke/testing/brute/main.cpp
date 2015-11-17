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

#define maxN 20011

int n, m, i, j;
pair< ll, ll > S[maxN];
ll x, y, R;

bool common(ll xx1, ll yy1, ll xx2, ll yy2,ll R) {
    ll val = 1LL * (xx2 - xx1) * (xx2 - xx1) +  1LL * (yy2 - yy1) * (yy2 - yy1);
    return 1LL * (xx2 - xx1) * (xx2 - xx1) +  1LL * (yy2 - yy1) * (yy2 - yy1) <= 1LL * R * R;
}

int main()
{
    freopen("nuke.in","r",stdin);
    freopen("nuke.ok","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%lld %lld", &S[i].first, &S[i].second);
    for (i = 1; i <= m; i++) {
        scanf("%lld%lld%lld", &x, &y, &R);

        int dead = 0;
        for (j = 1; j <= n; j++)
            if (common(S[j].first, S[j].second, x, y, R)) dead++;

        printf("%d\n", dead);
    }




    return 0;
}
