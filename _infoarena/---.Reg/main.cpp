#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2000011
#define maxVal 500011
#define bucket 1000000

int t, ti;
int n, k, i, dead;
ll A, B, C, X;
int nxt[bucket + 22];
int last[maxVal];
bitset<maxN> good;
bitset<maxVal> alrdn;
int act, ans;

int def;

void refresh(ll X, int pas) {
    int i;

    for (i = 1; i <= bucket; i++) nxt[i] = n + 1;
    memset(last, 0, sizeof(last));

    for (i = 1; i <= n - def; i++) {
        if (last[X] != 0 && last[X] <= bucket)
            nxt[ last[X] ] = def + i;
        last[X] = i;

        X = (A * X + B * (pas + i)) % C;
    }

    //for (i = 1; i <= n; i++) cerr << nxt[i] << ' ';
    //cerr << '\n';
}

int main()
{
    freopen("reg.in","r",stdin);
    freopen("reg.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%lld%lld%lld%d%d", &A, &B, &C, &n, &k);

        dead = n + 1;
        good.reset();
        alrdn.reset();
        act = 0; def = -bucket;

        ans = 1; X = 1;
        for (i = 1; i <= n && i < dead; i++) {

            if ( (i - 1) % bucket == 0 ) {
                def += bucket;
                refresh(X, i);
            }

            //! start new batch
            if (alrdn[X] == false) {
                act++;
                alrdn[X] = true;
            }

            //! close a batch
            if (act > k) {
                dead--;
                while (dead > i && good[dead] == false) dead--;
                if (dead == i) break;
                act--;
            }

            //! add next process
            if (nxt[i - def] >= dead)
                act--;
            else
                good[ nxt[i - def] ] = true;

            ans = i;
            X = (A * X + B * (i + 1)) % C;
        }

        printf("%d\n", ans);
        cerr << ans << '\n';
    }


    return 0;
}
