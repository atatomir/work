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

#define maxN 555

int n, m, ln, co, i, j;
ll ans[maxN][maxN], sum, bonus;


int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d%d", &n, &m, &ln, &co);

    if (ln * co == 1) {
        printf("No");
        return 0;
    }

    bonus = 1000000000 / (ln * co - 1);
    if (bonus * (ln * co - 1) + 1 > 1000000000) bonus--;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            ans[i][j] = bonus;

    for (i = ln; i <= n; i += ln) {
        for (j = co; j <= m; j += co) {
            ans[i][j] = -(bonus * (ln * co - 1) + 1);
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            sum += ans[i][j];

    if (sum < 0) {
        printf("No");
        return 0;
    }

    printf("Yes\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            printf("%lld ", ans[i][j]);
        }
        printf("\n");
    }


    return 0;
}
