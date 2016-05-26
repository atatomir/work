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

#define maxN 100001
#define def 100

int t, lim, i, a, b;

int w[def + 10][def + 10];
vector< pair<int, int> > rez;

int dead[maxN];

void precomp() {
    int i, j, k, l;

    for (i = 0; i <= def; i++) {
        for (j = 0; j <= def; j++) {
            w[i][j] = 0;

            for (k = 1; k <= i; k++)
                w[i][j] |= 1 ^ w[i - k][j];

            for (k = 1; k <= j; k++)
                w[i][j] |= 1 ^ w[i][j - k];

            for (k = 1; k <= i; k++)
                for (l = 1; l <= j; l++)
                    if ( max(k, l) - min(k, l) <= lim )
                        w[i][j] |= 1 ^ w[i - k][j - l];

            if (i <= j)
                cerr << w[i][j] << ' ';
            else
                cerr << "- ";

            if (i <= j && w[i][j] == 0)
                rez.pb(mp(i, j));
        }

        cerr << '\n';
    }

    for (auto e : rez)
        cerr << e.first << ' ' << e.second << '\n';
}

void compute() {
    int i, last;
    int bonus;

    dead[0] = 0; last = 0; bonus = 0;

    for (i = 1; i < maxN; i++) {
        if (dead[i]) {
            bonus = 1;
            continue;
        }

        int pp = last + lim + 2 + bonus;
        dead[i] = pp;
        if (pp < maxN) dead[pp] = i;
        bonus = 0;
        last = pp;
    }
}

int main()
{
    freopen("alinuta.in","r",stdin);
    freopen("alinuta.out","w",stdout);

    scanf("%d%d", &lim, &t);


    /*precomp();
    for (i = 1; i <= t; i++) {
        scanf("%d%d", &a, &b);
        if (w[a][b])
            printf("A\n");
        else
            printf("B\n");
    }*/

    compute();
    for (i = 1; i <= t; i++) {
        scanf("%d%d", &a, &b);
        if (dead[a] != b)
            printf("A\n");
        else
            printf("B\n");
    }



    return 0;
}
