#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 200011
#define mod 1000000007LL
#define ll long long

int t, test;
int n, i;
pair<ll, ll> v[maxN];

stack<int> S;
ll sum_one[maxN];
ll sum_two[maxN];
ll ans;
ll cnt[maxN];

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        cerr << "S" << test << '\n';

        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            scanf("%lld%lld", &v[i].first, &v[i].second);

        sort(v + 1, v + n + 1);
        while (!S.empty()) S.pop();

        memset(sum_one, 0, sizeof(sum_one));
        memset(sum_two, 0, sizeof(sum_two));
        memset(cnt, 0, sizeof(cnt));
        ans = 0;

        for (i = 1; i <= n; i++) {
            while (!S.empty()) {
                int id = S.top();
                auto now = v[id];

                if (now.second >= v[i].second) break;

                S.pop();
            }

            if (!S.empty()) {
                int id = S.top();
                auto now = v[id];

                if (now.second != v[i].second) {
                    sum_one[i] = sum_two[i] = cnt[i] = 0;
                } else {

                    ll dif = v[i].first - now.first;
                    ll dif_sq = (dif * dif) % mod;

                    sum_two[i] = ((sum_two[id] + ((cnt[id] * dif_sq) % mod)) % mod) + 2 * ((dif * sum_one[id]) % mod);
                    sum_two[i] = (sum_two[i] + dif_sq) % mod;

                    sum_one[i] = (sum_one[id] + (dif * (cnt[id] + 1))) % mod;

                    cnt[i] = cnt[id] + 1;

                    ans = (ans + sum_two[i]) % mod;

                }
            }

            S.push(i);
        }

        printf("Case #%d: %lld\n", test, ans);
    }


    return 0;
}
