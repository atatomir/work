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

#define maxN 22
#define maxM 35

#define lsb(x) ( (x & (x - 1)) ^ x )
#define sorted(x) ((x + lsb(x)) & full) == 0

int n, m, i, j, x, y, limit, dif, full, state, diff_state;
int sw[maxM][maxN];
int last[maxM];
int cnt;


void trace(int dif) {
    static int i, p1, p2, aux;
    last[0] ^= 1 << dif;

    for (i = 1; i <= m; i++) {
        //! check if you have already finished your work
        if (sorted(last[i - 1]))
            for (; i <= m; i++)
                last[i] = last[i - 1];

        //! compute next dif
        p1 = dif;
        p2 = sw[i][dif];

        if (p1 > p2) swap(p1, p2);
        aux = last[i - 1];

        if ( (aux & (1 << p1)) > (aux & (1 << p2)))
            aux ^= (1 << p1) | (1 << p2);

        if ( (aux & (1 << p1)) != (last[i] & (1 << p1)))
            dif = p1;
        else
            dif = p2;

        last[i] ^= (1 << dif);
    }
}

int main()
{
    freopen("sortnet.in","r",stdin);
    freopen("sortnet.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n / 2; j++) {
            scanf("<%d,%d> ", &x, &y);
            sw[i][x - 1] = y - 1;
            sw[i][y - 1] = x - 1;
        }
    }

    full = (1 << n) - 1;

    cnt = 1;
    limit = 1 << n;
    for (i = 1; i < limit; i++) {
        state = i ^ (i >> 1);

        dif = 0;
        int diff_state = state ^ last[0];
        while (diff_state != 1) {
            dif++;
            diff_state >>= 1;
        }

        trace(dif);

        if (sorted(last[m])) cnt++;
    }


    printf("%d", cnt);

    return 0;
}
