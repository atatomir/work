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

#define pii pair<int, int>
#define maxN 111
#define maxL 555
#define lim 20
#define inf 1000000000

int n, m, l, i, j, pos, cnt, k, limit;
char aux[maxL];
vector<string> A;
string B, act;
int from[maxL];

pii dp[maxN][maxL];
//! first - cost, second - moves

pii ans;
int add_cost[maxN];
int rez;

string get_str() {
    string ans = "";

    while (pos <= n && aux[pos] == ' ') pos++;
    while (pos <= n && aux[pos] != ' ') {
        ans.pb(aux[pos]);
        rez += abs(aux[pos] - '@');
        pos++;
    }
    while (pos <= n && aux[pos] == ' ') pos++;

    return ans;
}

int abs(int x) {
    if (x < 0) return -x;
    return x;
}

pii compute(int id, int l, int r) {
    int cost = 0;
    int moves = 0;

    int limit = min(r - l + 1, (int)A[id].size());

    for (int i = 0; i < limit; i++)
        cost += abs(0 + A[id][i] - B[l + i]);
    for (int i = limit; i < A[id].size(); i++)
        cost += abs(0 + A[id][i] - '@');
    for (int i = limit; i < r - l + 1; i++)
        cost += abs(0 + B[l + i] - '@');

    for (int i = l; i <= r; i++)
        moves += abs(id - from[i]);

    return mp(cost, moves);
}

pii sum(pii a, pii b) {
    a.first += b.first;
    a.second += b.second;

    return a;
}


int main()
{
    freopen("dist.in","r",stdin);
    freopen("dist.out","w",stdout);

    //! get A
    gets(aux + 1);
    n = strlen(aux + 1);
    pos = 1;

    while (pos <= n) {
        rez = 0;
        A.pb( get_str() );
        add_cost[ A.size() - 1 ] = rez;
    }

    for (i = n - 2; i >= 0; i--)
        add_cost[i] += add_cost[i + 1];

    //! get B
    memset(aux, 0, sizeof(aux));
    gets(aux + 1);
    n = strlen(aux + 1);
    pos = 1;

    while (pos <= n) {
        int p1 = B.size();
        B +=  get_str() ;

        for (i = p1; i < B.size(); i++) from[i] = cnt;
        cnt++;
    }

    n = max( (int)A.size(), cnt);
    l = B.size();

    while (A.size() != n) A.pb("");

    //! compute dp[0]
    int limit = min(l, lim);
    for (i = 0; i < limit; i++)
        dp[0][i] = compute(0, 0, i);

    for (i = limit; i < l; i++)
        dp[0][i] = mp(inf, inf);


    for (i = 1; i < n; i++) {
        for (j = 0; j < l ; j++) {
            limit = max(1, j - lim + 1);

            dp[i][j] = mp(inf, inf);

            for (k = limit; k <= j; k++) {
                dp[i][j] = min(dp[i][j], sum(dp[i - 1][k - 1], compute(i, k, j))  );
            }
        }
    }


    ans = mp(inf, inf);
    for (i = 0; i < n; i++)
        ans = min(ans, sum(dp[i][l - 1], mp(add_cost[i + 1], 0)));

    printf("%d %d", ans.first, ans.second);

    return 0;
}
