#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 18  //! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
#define maxDim 1024
#define inf 1000000000000000000LL
#define piii pair< int, int>

struct Airport {
    ll x1, x2, y1, y2;

    void read() {
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
    }
};

int n, i, cities, k, j, state, now;
Airport Air[maxN];
vector< vector<ll> > street;
vector<ll> aux;

int st, en;
int lim;
ll dp[maxN][1 << maxN];

vector<int> bits[1 << maxN];
ll ans, x;
ll dist[maxN][maxN];

queue< piii > Q;

void add_best_edge(vector<ll>& A, vector<ll>& B) {
    ll best = inf;

    int pos = 0;
    for (auto e : A) {
        while (pos + 1 < B.size()) {
            if (e < B[pos + 1]) break;
            pos++;
        }

        if (e >= B[pos])
            best = min(best, e - B[pos]);
    }

    pos = 0;
    for (auto e : B) {
        while (pos + 1 < A.size()) {
            if (e < A[pos + 1]) break;
            pos++;
        }

        if (e >= A[pos])
            best = min(best, e - A[pos]);
    }

    ans += best * best;
}


int main()
{
    freopen("campanie.in","r",stdin);
    freopen("campanie.out","w",stdout);

    scanf("%d", &cities);
    for (int city = 0; city < cities; city++) {
        Air[city].read();
        scanf("%d", &n);
        for (i = 1; i < n; i++) {
            scanf("%lld", &x);
            ans += x * x;
        }

        street.clear();
        for (i = 1; i <= n; i++) {
            scanf("%d", &k);

            aux.resize(k);
            for (j = 0; j < k; j++)
                scanf("%lld", &aux[j]);

            sort(aux.begin(), aux.end());
            street.pb(aux);
        }

        for (i = 1; i < street.size(); i++)
            add_best_edge(street[i - 1], street[i]);

        cerr << ans << '\n';
    }

    //! ------------------------------------------------------

    n = cities;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = (Air[i].x2 - Air[j].x1) * (Air[i].x2 - Air[j].x1) +
                         (Air[i].y2 - Air[j].y1) * (Air[i].y2 - Air[j].y1) ;

    lim = (1 << n);
    for (state = 1; state < lim; state++)
        for (i = 0; i < n; i++)
            if ((state & (1 << i)) == 0)
                bits[state].pb(i); //! not selected bits

    ll mini = inf;
    for (st = 0; st < 1; st++) {
        memset(dp, 0, sizeof(dp));
        Q.push(mp(st, 1 << st));

        while (!Q.empty()) {
            en = Q.front().first;
            state = Q.front().second;
            Q.pop();

            for (auto bit : bits[state]) {
                now = state | (1 << bit);

                if (dp[bit][now] == 0) {
                    dp[bit][now] = dp[en][state] + dist[en][bit];
                    Q.push(mp(bit, now));
                } else {
                    dp[bit][now] = min(dp[bit][now], dp[en][state] + dist[en][bit]);
                }
            }
        }


        for (j = 0; j < n; j++)
            if (st != j)
                mini = min(dp[j][lim - 1] + dist[j][st], mini);

    }

    printf("%lld", ans + mini);
    cerr << ans + mini << "\n";

    return 0;
}
