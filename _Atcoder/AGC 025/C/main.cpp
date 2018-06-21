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

const int maxN = 100011;

int n, i, x, y;
vector<int> le, ri;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        le.pb(x);
        ri.pb(y);
    }

    le.pb(0);
    ri.pb(0);

    sort(le.begin(), le.end());
    reverse(le.begin(), le.end());
    sort(ri.begin(), ri.end());

    for (i = 0; i < le.size(); i++) {
        int a = ri[i];
        int b = le[i];
        if (a >= b) break;
        ans += 1LL * (b - a);
    }

    ans *= 2LL;
    printf("%lld", ans);



    return 0;
}
