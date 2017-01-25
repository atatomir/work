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

#define maxN 3011
#define mod 1000000007

int n, m, i, j, l, r, maxi;
char s[maxN];
int sum[maxN];
vector< pair<int, int> > ord, aux;

ll comb[maxN][maxN];
ll ans;
ll dp[maxN][maxN];


void pre() {
    int i, j;

    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= mod) comb[i][j] -= mod;
        }
    }
}

ll sumi(ll x, ll y) {
    return sum[y] - sum[x - 1];
}

ll solve(int bg, int en) {
    int i, j, k, l, r, new_l, new_r, intr_dim, dim;
    int nr0, nr1, posl, posr, to;

    aux.clear();
    for (i = bg; i < en; i++)
        aux.pb(ord[i]);

    for (i = 0; i <= aux.size(); i++)
        memset(dp[i], 0, sizeof(dp[i]));

    dp[0][sumi(aux[0].first, aux[0].second)] = 1;
    for (i = 0; i + 1 < aux.size(); i++) {
        l = aux[i].first;
        r = aux[i].second;
        dim = r - l + 1;

        new_l = aux[i + 1].first;
        new_r = aux[i + 1].second;
        intr_dim = new_l - l;

        for (j = 0; j <= dim; j++) {
            if (dp[i][j] == 0) continue;

            nr1 = j;
            nr0 = dim - nr1;

            posl = max(0, intr_dim - nr0);
            posr = min(intr_dim, nr1);

            for (k = posl; k <= posr; k++) {
                to = j - k + sumi(r + 1, new_r);
                dp[i + 1][to] += (dp[i][j] * comb[intr_dim][k]) % mod;
                if (dp[i + 1][to] >= mod) dp[i + 1][to] -= mod;
            }
        }
    }

    l = aux.back().first;
    r = aux.back().second;
    dim = r - l + 1;

    ll ans = 0;
    for (i = 0; i <= dim; i++)
        ans += ( dp[aux.size() - 1][i] * comb[dim][i] ) % mod;

    return ans % mod;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n%s", &n, &m, s + 1);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &l, &r);
        ord.pb(mp(l, r));
    }

    sort(ord.begin(), ord.end(), [](const pair<int, int>& a, const pair<int, int>& b)->bool const {
        return mp(a.first, -a.second) < mp(b.first, -b.second);
    });

    aux = ord;
    ord.clear();

    maxi = 0;
    for (auto e : aux)
        if (e.second > maxi)
            maxi = e.second, ord.pb(e);

    pre();
    for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + s[i] - '0';
    ans = 1;

    for (i = 0; i < ord.size(); i = j) {
        for (j = i + 1; j < ord.size(); j++)
            if (ord[j - 1].second < ord[j].first)
                break;

        ans = (ans * solve(i, j)) % mod;
    }

    printf("%lld", ans);


    return 0;
}
