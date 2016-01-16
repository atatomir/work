#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011

int t, i, a, b, cnt;
int lose[maxN];

int main()
{
    freopen("pietre.in","r",stdin);
    freopen("pietre.out","w",stdout);

    lose[0] = 0;
    for (i = 1; i <= 1000000; i++) {
        if (lose[i]) continue;

        cnt++;
        lose[i] = i + cnt;
        if (i + cnt < 1000000)
            lose[i + cnt] = i;
    }

    scanf("%d", &t);
    for (i = 1; i <= t; i++) {
        scanf("%d%d", &a, &b);
        if (lose[a] == b)
            printf("2\n");
        else
            printf("1\n");
    }


    return 0;
}
