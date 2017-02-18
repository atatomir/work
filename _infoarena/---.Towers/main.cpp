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
#define ll long long

#define maxN 1000011

int n, k, i, x, pos, ans, old;
int h[maxN], dp[maxN];
vector< pair<int, int> > Q, offer;
vector<int> list[maxN];

stack<int> S;
int sol[maxN];


int main()
{
    freopen("towers.in","r",stdin);
    freopen("towers.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (i = 1; i <= k; i++) {
        scanf("%d", &x);
        Q.pb(mp(x, i));
    }

    h[0] = 1000000002;
    h[n + 1] = 1000000001;

    S.push(0);

    for (i = 1; i <= n + 1; i++) {
        dp[i] = 1;

        while (!S.empty()) {
            if (h[S.top()] > h[i]) break;

            old = S.top();
            S.pop();

            dp[S.top()] = max(dp[S.top()], dp[old] + 1);
        }

        list[S.top()].pb(i);
        S.push(i);
    }

    for (i = 1; i <= n; i++)
        offer.pb(mp(h[i], dp[i]));


    sort(offer.begin(), offer.end());
    sort(Q.begin(), Q.end());

    ans = pos = 0;
    for (auto e : Q) {
        while (pos < offer.size()) {
            if (offer[pos].first > e.first) break;
            ans = max(ans, offer[pos].second);
            pos++;
        }

        sol[e.second] = ans;
    }

    for (i = 1; i <= k; i++)
        printf("%d ", sol[i]);

    return 0;
}
