#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2016
#define ll long long

int n, i, j, k, t;
pair<ll, ll> P[maxN];
ll ans;
vector<ll> aux;

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);

    for (int test; test <= t; test++) {
        ans = 0;

        cerr << "Solving " << test << '\n';

        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            scanf("%lld %lld", &P[i].first, &P[i].second);

        for (i = 1; i <= n; i++) {
            aux.clear();

            for (j = 1; j <= n; j++) {
                if (i == j) continue;
                ll dist = (P[i].first - P[j].first) * (P[i].first - P[j].first) +
                          (P[i].second - P[j].second) * (P[i].second - P[j].second);
                aux.pb(dist);
            }

            sort(aux.begin(), aux.end());

            for (int pos = 0; pos < aux.size(); pos++) {
                ll cnt = 1;
                ll val = aux[pos];

                while (pos + 1 < aux.size()) {
                    if (aux[pos + 1] != val) break;
                    pos++;
                    cnt++;
                }

                ans += (cnt * (cnt - 1)) / 2LL;
            }
        }

        printf("Case #%d: %lld\n", test, ans);

    }


    return 0;
}
