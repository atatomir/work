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

int n, i, j, k, l;
pair<int, int> P[maxN];
vector<int> v;
int ans = 1000000000;

int main()
{
    freopen("drept.in","r",stdin);
    freopen("drept.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second);
    sort(P + 1, P + n + 1);

    for (i = 1; i + k - 1 <= n; i++) {
        v.clear();

        for (j = i; j <= n; j++) {
            v.insert( lower_bound(v.begin(), v.end(), P[j].second), P[j].second );
            for (l = 0; l + k - 1 < v.size(); l++)
                ans = min(ans, (P[j].first - P[i].first) * (v[l + k - 1] - v[l]));
        }
    }

    printf("%d", ans);


    return 0;
}
