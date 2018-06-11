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

const int maxN = 1024;
const ll inf = 1LL << 50;

ll n, i, j;
ll a[maxN], sum[maxN];
vector<int> moves;

pair<ll, ll> dp[maxN][maxN];
pair<ll, pair<ll, ll> > best;

void rm_back(int cnt) {
    while (cnt-- > 0) {
        moves.pb(n);
        n--;
    }
}

void rm_front(int cnt) {
    while (cnt-- > 0) {
        moves.pb(1);
    }
}

void compute_dp() {
    int i, j, k;
    best = mp(-inf, mp(-1, -1));

    for (i = n; i > 0; i--) {
        dp[i][i] = mp(a[i], 0);
        best = max(best, mp(a[i], mp(1LL * i, 1LL * i)));

        for (j = i + 1; j <= n; j++) {
            if (i % 2 == j % 2) {
                //! full group
                dp[i][j] = mp(-inf, -1);
                for (k = 1; j - k >= i + 1; k += 2)
                    dp[i][j] = max(dp[i][j], mp(dp[i][j - k].first + dp[j - k + 1][j].first, 1LL * j - k));

                best = max(best, mp(dp[i][j].first, mp(1LL * i, 1LL * j)));
            } else {
                //! partial group
                dp[i][j] = mp(dp[i][j - 1].first, j - 1);
                if (j - 2 >= i) dp[i][j] = max(dp[i][j], dp[i][j - 2]);
            }
        }
    }

}

void rev(int l, int r) {
    if (l == r) return;

    if (l % 2 == r % 2) {
        //! full group
        rev(dp[l][r].second + 1, r);
        rev(l, dp[l][r].second);
    } else {
        //! partial group
        rev(dp[l][r].second + 1, r);
        rev(l, dp[l][r].second);
        moves.pb(l + 1);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = a[i];

        if (i >= 3) sum[i] += sum[i - 2];
    }

    compute_dp();
    rm_back(n - best.second.second);
    rev(best.second.first, best.second.second);
    rm_front(best.second.first - 1);


    cout << best.first << '\n';
    cout << moves.size() << '\n';
    for (auto e : moves) cout << e << '\n';



    return 0;
}
