#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define inf 1000000000

int n, i, t, test;
int v[maxN];
int dp[maxN];

bool good(int id1, int id2) {
    int i;
    vector<int> aux;

    aux.clear();
    for (i = id1; i <= id2; i++)
        aux.pb(v[i]);

    for (i = 1; i < aux.size(); i++)
        if (aux[i - 1] >= aux[i])
            return false;

    if (aux.size() == 1)
        return true;
    if (aux.size() == 2)
        return (aux[1] - aux[0]) <= 30;
    if (aux.size() == 3) {
        int d1 = aux[1] - aux[0];
        int d2 = aux[2] - aux[1];

        if (d1 > d2) swap(d1, d2);
        if (d1 > 10) return false;
        if (d2 > 20) return false;
        return true;
    }
    if (aux.size() == 4) {
        int max_dif = aux[1] - aux[0];
        max_dif = max(max_dif, aux[2] - aux[1]);
        max_dif = max(max_dif, aux[3] - aux[2]);

        return (max_dif <= 10);
    }
}

int solve() {
    int i, j, k;

    //sort(v + 1, v + n + 1); //! no sort is allowed
    dp[0] = 0;

    for (i = 1; i <= n; i++) {
        dp[i] = inf;

        int lim = max(1, i - 3);
        for (j = i; j >= lim; j--) {
            if (good(j, i))
                dp[i] = min(dp[i], dp[j - 1] + (4 - (i - j + 1)) );
        }
    }

    return dp[n];
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    for (scanf("%d", &t), test = 1; test <= t; test++) {
        cerr << "Solving " << test << '\n';

        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d", &v[i]);
        printf("Case #%d: %d\n", test,  solve() );
    }


    return 0;
}
