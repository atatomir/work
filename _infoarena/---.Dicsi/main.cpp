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

int n, i, j, cnt;
int ans[maxN];
int aux[maxN];

int main()
{
    freopen("dicsi.in","r",stdin);
    freopen("dicsi.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) aux[i] = i, ans[i] = 1;
    cnt = 1;

    for (i = 2; i <= n; i++) {
        for (j = i; j <= n; j += i) {
            while (aux[j] % i == 0) {
                cnt = max(cnt, ++ans[j]);
                aux[j] /= i;
            }
        }
    }

    printf("%d\n", cnt);
    for (i = 1; i <= n; i++)
        printf("%d ", ans[i]);


    return 0;
}
