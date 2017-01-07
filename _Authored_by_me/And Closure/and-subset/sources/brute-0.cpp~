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

#define maxN 1024

ll n, i;
ll v[maxN];
vector<ll> ans;

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    scanf("%lld", &n);
    for (i = 0; i < n; i++) scanf("%lld", &v[i]);

    ans.pb(0);

    ll mask = (1 << n) - 1;
    for (int conf = mask; conf > 0; conf--) {
        ll aux = (1 << 20) - 1;

        for (i = 0; i < n; i++)
            if ( (conf >> i) & 1 )
                aux &= v[i];

        ans.pb(aux);
    }

    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%lld ", e);


    return 0;
}
