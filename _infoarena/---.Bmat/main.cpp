#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024
#define mod 666013LL

int n, m, i, j, k;
char game[maxN][maxN];

int how;
bool know = false;
bool isOne = false;

long long myPow(long long a, long long b) {
    long long ans = 1;

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

int main()
{
    freopen("bmat.in","r",stdin);
    freopen("bmat.out","w",stdout);

    scanf("%d%d%d\n", &n, &m, &k);
    for (i = 1; i <= n; i++) {
        for (j = 1; j < m; j++) scanf("%c ", &game[i][j]);
        scanf("%c\n", &game[i][m]);
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (game[i][j] == '?')
                how++;

    for (i = n % k; i <= n; i += k) {
        for (j = m % k; j <= m; j += k) {
            if (game[i][j] == '?') know = true;
            if (game[i][j] == '1') isOne ^= true;
        }
    }

    if (know == false && isOne == false) {
        printf("0");
        return 0;
    }

    if (know) how--;

    printf("%lld", myPow(2, how));

    return 0;
}
