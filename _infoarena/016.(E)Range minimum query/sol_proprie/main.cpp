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

#define maxN 100011
#define maxM 1000011

int n, m, i, r;
int v[maxN];
int qq[maxM];
vector<int> Q[maxN];
int ans[maxM];

int dim;
int S[maxN];

int dad[maxN];



int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

void Merge(int son, int daddy) {
    dad[son] = daddy;
}



int main()
{
    freopen("rmq.in","r",stdin);
    freopen("rmq.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]), dad[i] = i;
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &qq[i], &r);
        Q[r].pb(i);
    }

    v[0] = -1000;

    S[dim = 1] = 0;
    for (i = 1; i <= n; i++) {
        while (v[i] <= v[ S[dim] ])
            Merge(S[dim--], i);
        S[++dim] = i;

        for (auto id : Q[i])
            ans[id] = v[Find(qq[id])];
    }

    for (i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
