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

#define maxN 50011
#define maxDig 7

int n, d, i, j;
char id[maxN][maxDig];

int state;
vector<int> bits;
vector<int> work;
int aux;

ll ans[maxDig];
ll act;

ll comb[maxDig][maxDig];


int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &d);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", id[i] + 1);
        for (j = 1; j <= 4; j++) {
            if ('0' <= id[i][j] && id[i][j] <= '9')
                id[i][j] = id[i][j] - '0';
            else
                id[i][j] = id[i][j] - 'a' + 11;
        }
    }

    for (state = 0; state < (1 << 4); state++) {
        bits.clear();
        for (i = 0; i < 4; i++)
            if ( (state >> i) & 1 )
                bits.pb(i);

        work.clear();
        for (i = 1; i <= n; i++) {
            aux = 0;
            for (int bb = 0; bb < bits.size(); bb++)
                aux = aux * 40 + id[i][1 + bits[bb]];

            work.pb(aux);
        }

        sort(work.begin(), work.end());

        act = 0;
        for (i = j = 0; i < work.size(); i++) {
            while (work[j] != work[i]) j++;
            act += 0LL + i - j;
        }

        ans[4 - bits.size()] += act;
    }

    for (i = 0; i <= 4; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++)
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
    }

    for (i = 1; i <= 4; i++) {
        for (j = 0; j < i; j++) {
            ans[i] -= ans[j] * comb[4 - j][i - j];
        }
    }

    printf("%lld", ans[d]);


    return 0;
}
