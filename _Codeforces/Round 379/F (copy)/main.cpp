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

#define maxN 200011

int n, i;
ll b[maxN], c[maxN];
ll fix[maxN];
ll ans[maxN];
int  da;

void no_sol() {
    printf("-1");
    exit(0);
}

void solve_bit(int bit) {
    int i;
    ll bb, cc;
    ll par = -1;
    ll cnt;
    ll pp = 1LL << bit;
    da = 0;

    for (i = 1; i <= n; i++) {
        fix[i] = -1;

        da |= b[i];
        da |= c[i];

        bb = (b[i] >> bit) & 1;
        cc = (c[i] >> bit) & 1;

        if (bb != 0) { // it is 1
            if (par == 0) no_sol();
            if (cc != n % 2) no_sol();
            par = 1;

            fix[i] = 1;
            continue;
        }

        if (cc != n % 2) { // it is 0
            if (par == (1 ^ cc)) no_sol();
            par = cc;

            fix[i] = 0;
            continue;
        }
    }

    if (da == 0) return ;

    for (i = 1; i <= n; i++) {

        bb = (b[i] >> bit) & 1;
        cc = (c[i] >> bit) & 1;

        if (bb != 0) { // it is 1
            continue;
        }

        if (cc != n % 2) { // it is 0
            continue;
        }

        fix[i] = 1; par = n % 2;
        /*if (par == -1)
            fix[i] = 1, par = n % 2;
        else
            fix[i] = par;*/
        //fix[i] = max(0LL, par);
    }


    cnt = 0;
    for (i = 1; i <= n; i++) cnt += (fix[i] == 1);
    if (cnt % 2 != par) no_sol();

    for (i = 1; i <= n; i++) {
        if (fix[i] == 1) {
            b[i] -= cnt * pp;
            c[i] -= n * pp;
        } else {
            c[i] -= cnt * pp;
        }
    }

    for (i = 1; i <= n; i++)
        if (fix[i] == 1)
            ans[i] |= pp;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &b[i]);
    for (i = 1; i <= n; i++) scanf("%lld", &c[i]);

    da = 1;
    for (int bit = 0; bit <= 30 && da; bit++) {
        solve_bit(bit);
    }

    for (i = 1; i <= n; i++) printf("%lld ", ans[i]);


    return 0;
}
