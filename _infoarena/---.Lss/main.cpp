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

int k, n, i, x;
vector<int> v;
ll ans;

int main()
{
    freopen("lss.in","r",stdin);
    freopen("lss.out","w",stdout);

    scanf("%d%d", &k, &n); ans = n;
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        v.pb(x - 1);
    }

    int pos;

    sort(v.begin(), v.end());
    for (i = 0; i < v.size(); i++) {
        pos = v[i] % k;
        pos = max(0, pos - i);

        ans += 1LL * pos;
    }

    printf("%lld", ans);


    return 0;
}
