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

#define maxN 111
#define inf 1000000000

int n, dim, i, j;

int v[maxN];
char sgn[maxN];

int dp_max[maxN][maxN];
int dp_min[maxN][maxN];


vector<int> who;
int best;

int compute_min(int l, int r);

int compute_max(int l, int r) {
    if (dp_max[l][r] != -inf) return dp_max[l][r];
    if (l == r) {
        dp_max[l][r] = v[l];
        return dp_max[l][r];
    }

    int aux, aux2;

    for (int i = l; i < r; i++) {
        if (sgn[i + 1] == 't')
            aux = compute_max(l, i) + compute_max(i + 1, r);
        else {
            aux = max(compute_max(l, i) * compute_min(i + 1, r), compute_min(l, i) * compute_max(i + 1, r)) ;
            aux2 = max(compute_max(l, i) * compute_max(i + 1, r), compute_min(l, i) * compute_min(i + 1, r));

            aux = max(aux, aux2);
            aux = aux2;
        }

        dp_max[l][r] = max(dp_max[l][r], aux);
    }

    return dp_max[l][r];
}

int compute_min(int l, int r) {
    if (dp_min[l][r] != inf) return dp_min[l][r];
    if (l == r) {
        dp_min[l][r] = v[l];
        return dp_min[l][r];
    }

    int aux, aux2;

    for (int i = l; i < r; i++) {
        if (sgn[i + 1] == 't') {
            aux = compute_min(l, i) + compute_min(i + 1, r);
        } else {
            aux = min(compute_max(l, i) * compute_min(i + 1, r), compute_min(l, i) * compute_max(i + 1, r)) ;
            aux2 = min(compute_max(l, i) * compute_max(i + 1, r), compute_min(l, i) * compute_min(i + 1, r));

            aux = min(aux, aux2);
        }

        dp_min[l][r] = min(dp_min[l][r], aux);
    }

    return dp_min[l][r];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        scanf("%c %d ", &sgn[i], &v[i]);
        sgn[i + n] = sgn[i];
        v[i + n] = v[i];
    }

    dim = 2 * n;


    for (i = 1; i <= dim; i++)
        for (j = 1; j <= dim; j++)
            dp_max[i][j] = -inf, dp_min[i][j] = inf;

    best = -inf;
    for (i = 1; i <= n; i++) {
        int aux = compute_max(i, i + n - 1);

        if (aux > best) {
            best = aux;
            who.clear();
        }

        if (aux == best) {
            who.pb(i);
        }
    }

    printf("%d\n", best);
    sort(who.begin(), who.end());
    for (int e : who) printf("%d ", e);

    return 0;
}
