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

#define maxN 2017

const int def = 2000;

struct device {
    int t1, t2, d, v;
};

int n, i, j, pos, ss, dd;
device D[maxN];
int dpL[2][maxN], dpR[2][maxN];

int main()
{
    freopen("senzori.in","r",stdin);
    freopen("senzori.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d%d%d%d", &D[i].t1, &D[i].t2, &D[i].d, &D[i].v);

    ss = 0; dd = 1;
    for (i = 1; i <= n; i++) {
        dpL[dd][0] = dpR[dd][def] = max(dpL[ss][def], dpR[ss][0]);

        for (j = D[i].t1; j + D[i].d <= D[i].t2; j++) {
            dpL[dd][j + D[i].d] = max(dpL[dd][j + D[i].d], D[i].v + dpL[ss][j]);
            dpL[dd][j + D[i].d] = max(dpL[dd][j + D[i].d], D[i].v + dpR[ss][j + D[i].d]);

            dpR[dd][j] = max(dpR[dd][j], D[i].v + dpR[ss][j + D[i].d]);
            dpR[dd][j] = max(dpR[dd][j], D[i].v + dpL[ss][j]);
        }

        for (j = 1; j <= def; j++)
            dpL[dd][j] = max(dpL[dd][j], dpL[dd][j - 1]);

        for (j = def - 1; j >= 0; j--)
            dpR[dd][j] = max(dpR[dd][j], dpR[dd][j + 1]);

        swap(ss, dd);
    }

    int ans = max(dpL[ss][def], dpR[ss][0]);
    printf("%d", ans);
    cerr << ans;


    return 0;
}
