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

#define maxN 55
#define sigma 26

int n, i, dim, j;
char s[maxN];
int cnt[33], aux[33];

int main()
{
    freopen("test.in","r",stdin);

    for (i = 0; i < sigma; i++) cnt[i] = 55;

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        memset(s, 0, sizeof(s));
        memset(aux, 0, sizeof(aux));

        scanf("%s\n", s + 1);
        dim = strlen(s + 1);
        for (j = 1; j <= dim; j++) aux[ s[j] - 'a' ]++;

        for (j = 0; j < sigma; j++)
            cnt[j] = min(cnt[j], aux[j]);
    }

    for (i = 0; i < sigma; i++) {
        for (j = 1; j <= cnt[i]; j++)
            printf("%c", 'a' + i);
    }



    return 0;
}
