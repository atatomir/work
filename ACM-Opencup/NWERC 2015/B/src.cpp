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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 222;
const ll inf = 1LL << 50;

ll n, m, i, j, s, d, aux;
pair<ll, ll> p[maxN];
ll dp[2][maxN];
ll lf, rh, ans;
vector< pair<ll, ll> > to_dp;
vector< ll > to_greedy;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second > b.second;
    return a < b;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &p[i].first, &p[i].second);
    }

    sort(p + 1, p + n + 1, cmp);
    aux = inf;
    for (i = n; i >= 1; i--) {
        if (p[i].second >= aux) {
            to_greedy.pb(p[i].second - p[i].first);
        } else {
            aux = p[i].second;
            to_dp.pb(p[i]);
        }
    }

    for (i = 0; i < to_dp.size(); i++)
        p[i + 1] = to_dp[i];
    n = to_dp.size();
    sort(p + 1, p + n + 1);
    ans = -inf;

    sort(to_greedy.begin(), to_greedy.end());
    reverse(to_greedy.begin(), to_greedy.end());
    for (i = 1; i < to_greedy.size(); i++)
        to_greedy[i] += to_greedy[i - 1];
    
    s = 0; d = 1;
    dp[s][0] = 0;
    for (i = 1; i <= n; i++) dp[s][i] = -inf;

    for (int tm = 1; tm <= m; tm++) {
        for (i = 0; i <= n; i++) dp[d][i] = -inf;
        
        for (i = tm - 1; i <= n; i++) {
            lf = -inf;
            rh = +inf;

            for (j = i + 1; j <= n; j++) {
                lf = max(lf, p[j].first);
                rh = min(rh, p[j].second);

                if (lf >= rh) break;
                dp[d][j] = max(dp[d][j], dp[s][i] + rh - lf);
            }
        }

        if (to_greedy.size() + tm >= m) {
            if (tm != m)
                ans = max(ans, dp[d][n] + to_greedy[m - tm - 1]);
            else
                ans = max(ans, dp[d][n]);
        }
    
        swap(s, d);
    }

    printf("%lld", ans);



    return 0;
}
