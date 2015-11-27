#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 511
#define maxQ 500011
#define maxLog 10

struct query {
    short C, L1, L2;
    int id;

    query(int _C, int _L1, int _L2, int _id) {
        C = _C;
        L1 = _L1; L2 = _L2;
        id = _id;
    }
};

int n, m, i, q, L, C, L1, L2;
char s[maxN][maxN];
vector<query> Q[maxN];
int dp[maxN][maxN];
bool ans[maxQ];

int how[maxLog][maxN];
int rmq_aux[maxN];

void solve_batch(int L) {
    int i, j, actLog;

    if (Q[L].size() == 0)
        return;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (s[i][j] == '0')
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i - 1][j] + 1;
        }
    }

    for (i = 1; i <= n; i++)
        how[0][i] = 0;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (dp[i][j] < L)
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i][j - 1] + 1;

            how[0][i] = max(how[0][i], dp[i][j]);
        }
    }

    for (actLog = 1; actLog < maxLog; actLog++) {
        int go = 1 << (actLog - 1);
        int lim = n - (1 << actLog) + 1;

        for (i = 1; i <= lim; i++)
            how[actLog][i] = max(how[actLog - 1][i], how[actLog - 1][i + go]);
    }

    for (auto qq : Q[L]) {
        int L1 = qq.L1;
        int L2 = qq.L2;
        int dim = L2 - L1 + 1;
        int actLog = rmq_aux[dim];
        int bit = 1 << actLog;

        int vv = max(how[actLog][L1], how[actLog][L2 - bit + 1]);
        if (vv >= qq.C)
            ans[qq.id] = true;
        else
            ans[qq.id] = false;
    }
}

int main()
{
    freopen("lcdr.in","r",stdin);
    freopen("lcdr.out","w",stdout);

    scanf("%d%d%d\n", &n, &m, &q);
    for (i = 1; i <= n; i++)
        scanf("%s\n", s[i] + 1);
    for (i = 1; i <= q; i++) {
        scanf("%d%d%d%d", &L, &C, &L1, &L2);

        if (L1 > L2) swap(L1, L2);

        if (L1 + L - 1 > L2) continue;
        Q[L].pb(query(C, L1 + L - 1, L2, i));;
    }

    rmq_aux[1] = 0;
    for (i = 1; i <= n; i++) {
        rmq_aux[i] = rmq_aux[i - 1];
        if (i >= (1 << (rmq_aux[i] + 1)))
            rmq_aux[i]++;
    }

    for (i = 1; i <= n; i++)
        solve_batch(i);

    for (i = 1; i <= q; i++)
        printf( (ans[i] ? "1\n" : "0\n") );

    return 0;
}
