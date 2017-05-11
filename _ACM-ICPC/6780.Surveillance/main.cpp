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

#define maxN 2000011
#define maxLog 22

int hh[maxN];

template<typename T>
struct rmq {
    int dim, i, j, bg, sm;
    T data[maxLog][maxN];

    void init(int _dim, T* from) {
        dim = _dim;
        for (i = 1; i <= dim; i++) data[0][i] = from[i];

        for (i = 1; i <= hh[dim]; i++) {
            bg = 1 << i;
            sm = bg >> 1;

            for (j = 1; j + bg - 1 <= dim; j++)
                data[i][j] = max(data[i - 1][j], data[i - 1][j + sm]);
        }
    }

    T que(int l, int r) {
        l = max(1, l);
        r = min(dim, r);

        int sz = r - l + 1;
        int lg = hh[sz];

        return max(data[lg][l], data[lg][r - (1 << lg) + 1]);
    }
};

int n, k, i, j, l, r, who, ans;
pair<int, int> intr[maxN], from[maxN];
rmq< pair<int, int> > work;

int dad[maxLog][maxN];

void solve() {
    int i, ans, aux, act, toto, j;
    ans = k + 13;

    for (i = 1; i <= k; i++) {
        aux = 1;
        act = i;

        if (intr[i].second - intr[i].first + 1 == n)
            ans = 1;

        for (j = hh[2 * k]; j >= 0; j--) {
            toto = dad[j][act];

            if (intr[toto].second - intr[i].first + 1 < n && toto != 0) {
                act = toto;
                aux += 1 << j;
            }
        }

        act = dad[0][act];
        aux++;

        if (intr[act].second - intr[i].first + 1 >= n)
            ans = min(ans, aux);
    }

    if (ans > k)
        printf("impossible\n");
    else
        printf("%d\n", ans);
}

int main()
{
    freopen("test.in","r",stdin);

    for (i = 2; i < maxN; i++) hh[i] = 1 + hh[i / 2];

    while (scanf("%d%d", &n, &k) == 2) {

        for (i = 1; i <= k; i++) {
            scanf("%d%d", &intr[i].first, &intr[i].second);
            if (intr[i].first > intr[i].second) intr[i].second += n;

            intr[i + k] = intr[i];
            intr[i + k].first += n;
            intr[i + k].second += n;
        }

        for (i = 1; i <= 2 * n; i++) from[i] = mp(0, 0);
        for (i = 1; i <= 2 * k; i++)
            if (intr[i].first <= 2 * n)
                from[intr[i].first] = max(from[intr[i].first], mp(intr[i].second, i));

        work.init(2 * n, from);
        for (i = 1; i <= 2 * k; i++) {
            l = intr[i].first;
            r = intr[i].second;

            dad[0][i] = work.que(l + 1, r + 1).second;
        }

        for (i = 1; i <= hh[2 * k]; i++)
            for (j = 1; j <= 2 * k; j++)
                dad[i][j] = dad[i - 1][dad[i - 1][j]];

        ans = n + 13;
        solve();
    }


    return 0;
}
