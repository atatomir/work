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
#define sigma 26

int n, m, k, i, j, cnt;
ll x;
char s[maxN];
char ch[maxN][sigma + 4];
int wh[maxN];

ll pows[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d%lld\n", &n, &m, &k, &x);
    scanf("%s\n", s + 1);
    for (i = 1; i <= m; i++) scanf("%s\n", ch[i] + 1), sort(ch[i] + 1, ch[i] + k + 1);

    for (i = 1; i <= n; i++)
        if (s[i] == '#')
            wh[++cnt] = i;

    pows[0] = 1;
    for (i = 1; i <= n; i++) pows[i] = min(x + 1, pows[i - 1] * k);

    for (i = 1; i <= m; i++) {
        for (j = 1; pows[m - i] < x; j++)
            x -= pows[m - i];

        s[wh[i]] = ch[i][j];
    }

    printf("%s", s + 1);


    return 0;
}
