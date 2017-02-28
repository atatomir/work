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

int n, i, j;
ll a[maxN];
vector< pair<ll, int> > ord;

int mini;
ll ans[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        ord.pb(mp(a[i], i));
    }

    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());

    mini = n + 10;
    for (i = 0; i < ord.size(); i = j) {
        for (j = i; j < ord.size(); j++) {
            if (ord[i].first != ord[j].first) break;
            mini = min(mini, ord[j].second);
        }

        ll nxt = 0;
        if (j != ord.size()) nxt = ord[j].first;

        ans[mini] += (ord[i].first - nxt) * j;
    }

    for (i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);



    return 0;
}
