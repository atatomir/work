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
#define maxM 200011

int n, m, i, p, t;
pair<int, int> modif[maxM];
bool good[maxN];

bool good_min, good_max;

bool try_min(int p) {
    memset(good, 0, sizeof(good));
    good[p] = true;

    for (int i = 1; i <= m; i++)
        good[ modif[i].second ] = good[ modif[i].first ];

    for (int i = 1; i <= n; i++)
        if (!good[i])
            return false;

    return true;
}

bool try_max(int p) {
    memset(good, 0, sizeof(good));
    good[p] = true;

    for (int i = 1; i <= m; i++)
        good[ modif[i].first ] = good[ modif[i].second ];

    for (int i = 1; i <= n; i++)
        if (!good[i])
            return false;

    return true;
}

int main()
{
    freopen("minmaxstore.in","r",stdin);
    freopen("minmaxstore.out","w",stdout);

    for(scanf("%d", &t); t > 0; t--) {
        scanf("%d%d", &n, &m);

        for (i = 1; i <= m; i++) scanf("%d%d", &modif[i].first, &modif[i].second);
        reverse(modif + 1, modif + m + 1);

        scanf("%d", &p);
        good_min = try_min(p);

        scanf("%d", &p);
        good_max = try_max(p);

        if (good_min && good_max)
            printf("Popeala\n");
        if (good_min && !good_max)
            printf("Popel\n");
        if (!good_min && good_max)
            printf("Popita\n");
        if (!good_min && !good_max)
            printf("Comisarul\n");
    }


    return 0;
}
