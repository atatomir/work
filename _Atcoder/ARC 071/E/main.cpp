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

int n, m, q, i, l1, r1, l2, r2, aux1, aux2;
char S[maxN], T[maxN];
int sum_s[maxN], sum_t[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s\n%s\n", S + 1, T + 1);
    n = strlen(S + 1);
    m = strlen(T + 1);

    for (i = 1; i <= n; i++)
        sum_s[i] = sum_s[i - 1] + (S[i] == 'A');

    for (i = 1; i <= m; i++)
        sum_t[i] = sum_t[i - 1] + (T[i] == 'A');

    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);

        aux1 = 3 * n + 2 * (sum_s[r1] - sum_s[l1 - 1]) - (r1 - l1 + 1);
        aux2 = 3 * n + 2 * (sum_t[r2] - sum_t[l2 - 1]) - (r2 - l2 + 1);

        if (aux1 % 3 == aux2 % 3)
            printf("YES\n");
        else
            printf("NO\n");
    }


    return 0;
}
