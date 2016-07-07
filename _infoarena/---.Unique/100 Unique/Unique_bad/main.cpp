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
int n, i, pos_l, pos_r;
int v[maxN];

int dim;
int S[maxN];
int l[maxN], r[maxN];

int pos;
int last[maxN];
vector<int> to_check;
int aib[maxN];
int ans;


int zrs(int x) {
    return (x & (x - 1)) ^ x;
}

void add(int x, int v) {
    while (x <= n) {
        aib[x] += v;
        x += zrs(x);
    }
}

int sum(int x) {
    int ans = 0;

    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }

    return ans;
}

bool cmp(const int a, const int b) {
    return r[a] < r[b];
}

int main()
{
    freopen("unique.in","r",stdin);
    freopen("unique.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);

        v[0] = v[n + 1] = n + 3;

        S[ dim = 1 ] = 0;
        for (i = 1; i <= n; i++) {
            scanf("%d", &v[i]);

            while (v[S[dim]] <= v[i]) dim--;
            l[i] = S[dim] + 1;
            S[++dim] = i;
        }

        S[ dim = 1 ] = n + 1;
        for (i = n; i >= 1; i--) {
            while (v[S[dim]] <= v[i]) dim--;
            r[i] = S[dim] - 1;
            S[++dim] = i;

            to_check.pb(i);
        }

        sort(to_check.begin(), to_check.end(), cmp);

        memset(aib, 0, sizeof(aib));
        memset(last, 0, sizeof(last));

        r[n + 1] = n + 1;
        to_check.pb(n + 1);
        ans = 0;


        pos = 0;
        for (i = 1; i <= n; i++) {
            if (last[ v[i] ])
                add(last[ v[i] ], -1);
            add(i, +1);
            last[ v[i] ] = i;

            while (r[to_check[pos]] == i) {
                pos_l = l[to_check[pos]];
                pos_r = r[to_check[pos]];


                if (sum(pos_r) - sum(pos_l - 1) == v[to_check[pos]])
                    ans = max(ans, pos_r - pos_l + 1);

                pos++;
            }
        }

        printf("%d\n", ans);
    }


    return 0;
}
