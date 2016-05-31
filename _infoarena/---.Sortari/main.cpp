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

#define maxM 611

int t, ti;
int n, m, i, x, y, lim;
int p1[maxM], p2[maxM];

bool sorted(int act) {
    if (act == 0) return true;

    act += (act ^ (act - 1)) & act;
    return ( (act & lim) == 0 );
}

bool solve() {
    int i, state, act;

    for (state = 0; state <= lim; state++) {
        act = state;

        for (i = 1; i <= m; i++) {
            if (p1[i] & act)
                if ( (p2[i] & act) == 0 )
                    act ^= p1[i] ^ p2[i];

            if (sorted(act))
                break;
        }

        if (!(sorted(act)))
            return false;
    }

    return true;
}

int main()
{
    freopen("sortari.in","r",stdin);
    freopen("sortari.out","w",stdout);

    for (scanf("%d", &t), ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);
        for (i = 1; i <= m; i++) scanf("%d%d", &p1[i], &p2[i]), p1[i] = (1 << (p1[i] - 1)), p2[i] = (1 << (p2[i] - 1));
        lim = (1 << n) - 1;

        if (solve())
            printf("1\n");
        else
            printf("0\n");
    }


    return 0;
}
