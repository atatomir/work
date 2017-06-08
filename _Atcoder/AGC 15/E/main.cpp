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

#define maxN 200011
#define mod 1000000007

int n, i;
pair<int, int> ninja[maxN];
pair<int, int> ord[maxN];
vector<int> n1, n2;

int best, last;
ll sum[maxN];

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> ninja[i].first >> ninja[i].second;
        n1.pb(ninja[i].first);
        n2.pb(ninja[i].second);
    }

    sort(n1.begin(), n1.end());
    sort(n2.begin(), n2.end());

    for (i = 1; i <= n; i++) {
        ninja[i].first = lower_bound(n1.begin(), n1.end(), ninja[i].first) - n1.begin() + 1;
        ninja[i].second = lower_bound(n2.begin(), n2.end(), ninja[i].second) - n2.begin() + 1;
    }

    sort(ninja + 1, ninja + n + 1);

    best = 0;
    for (i = 1; i <= n; i++) {
        best = max(best, ninja[i].second);
        ord[i].second = best;
    }

    best = n + 1;
    for (i = n; i >= 1; i--) {
        best = min(best, ninja[i].second);
        ord[i].first = best;
    }

    sum[0] = 1; last = 0;
    for (i = 1; i <= n; i++) {
        while (last < ord[i].second) {
            sum[last + 1] = sum[last];
            last++;
        }

        sum[ord[i].second] += mod + sum[ord[i].second] - (ord[i].first - 1 != 0 ? sum[ord[i].first - 2] : 0);
        sum[ord[i].second] %= mod;
    }

    cout << (mod + sum[last] - sum[last - 1]) % mod;

    return 0;
}
