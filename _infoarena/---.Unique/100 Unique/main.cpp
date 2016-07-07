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

int t, ti;
int n, i;
int v[maxN];

int dim;
int S[maxN];

int last[maxN];
int ans;

int dad[maxN];
int uni[maxN];


int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;

    dad[x] = y;
    uni[y] += uni[x];
    return true;
}



int main()
{
    freopen("unique.in","r",stdin);
    freopen("unique.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);

        for (i = 1; i <= n; i++) dad[i] = i, scanf("%d", &v[i]);
        memset(uni, 0, sizeof(uni));
        memset(last, 0, sizeof(last));

        v[0] = n + 3; v[n + 1] = n + 1;
        ans = 0;
        S[dim = 1] = 0;

        for (i = 1; i <= n + 1; i++) {
            while (v[S[dim]] <= v[i]) {
                Merge(S[dim], i);
                if (uni[ Find(i) ] == v[S[dim]])
                    ans = max(ans, i - S[dim - 1] - 1);
                dim--;
            }
            S[++dim] = i;

            uni[ Find(i) ]++;
            if (last[ v[i] ]) uni[ Find(last[v[i]]) ]--;
            last[v[i]] = i;
        }

        printf("%d\n", ans);
    }


    return 0;
}
