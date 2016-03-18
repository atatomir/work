#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 333

template<typename T>
struct min_window {
    deque< pair<int, T> > data;

    void init() { data.clear(); }

    void operator<<(pair<int, T> act) {
        while (!data.empty()) {
            auto last = data.back();
            if (last.second < act.second) break;
            data.pop_back();
        }
        data.push_back(act);
    }

    void remove_until(int limit) {
        while (!data.empty()) {
            auto last = data.front();
            if (last.first >= limit) break;
            data.pop_front();
        }
    }

    pair<int, T> query() {
        assert(data.empty() == false);
        return data.front();
    }
};



int n, m, i, j;
int l_low, l_high, c_low, c_high;
ll mat[maxN][maxN];

ll sums[maxN][maxN];
ll work[maxN][maxN];
min_window<ll> window;
ll ans;

ll poss;


bool check(ll aim, double L) {
    int i, j;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            work[i][j] = (sums[i][j] / L) - aim;

    /*
     * now i have to find a row-sequence with more than c_low elements
     * and less than c_high elements which has the sum >= 0.
     * otherwise return false
     */

     for (i = L; i <= n; i++) {
        window.init();

        for (j = 1; j <= m; j++)
            work[i][j] += work[i][j - 1];

        for (j = c_low; j <= m; j++) {
            window << mp(j - c_low, work[i][j - c_low]);
            window.remove_until(j - c_high);

            if (work[i][j] - window.query().second >= 0) return true;
        }
     }

     return false;
}

void try_with(int L) {
    int i, j;

    //! make sums
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            sums[i][j] = sums[i - 1][j] + mat[i][j];
            if (i >= L)
                sums[i][j] -= mat[i - L][j];
        }
    }

    ll low = ans;
    ll high = poss;
    ll mid;

    while (low <= high) {
        mid = (low + high) >> 1;

        if (check(mid, L))
            low = mid + 1;
        else
            high = mid - 1;
    }

    ans = max(ans, high);
}


int main()
{
    freopen("balans.in","r",stdin);
    freopen("balans.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &l_low, &c_low);
    l_low = max(l_low, 1);
    c_low = max(c_low, 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%lld", &mat[i][j]);
            mat[i][j] *= 1000;
            mat[i + n][j] = mat[i][j + m] = mat[i + n][j + m] = mat[i][j];

            poss = max(poss, mat[i][j]);

        }
    }

    l_high = n;
    c_high = m;

    n *= 2;
    m *= 2;

    for (i = l_low; i <= l_high; i++)
        try_with(i);


    double d_ans = 1.00 * ans / 1000.00;
    printf("%.3lf", d_ans);


    return 0;
}
