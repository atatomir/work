#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 33
#define lim (1 << 17)
#define popcount(x) vrajeala[x >> 17] + vrajeala[x & mask2]

int n, a, b, i, j, mask;
char s[maxN];
int adj[maxN];

int cnt;
ll comb[maxN][maxN];
ll ans;

int vrajeala[lim], mask2;

void pre() {
    int i, j;

    comb[0][0] = 1;
    for (i = 1; i <= n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= b && j <= i; j++)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }

    mask2 = (1 << 17) - 1;
    for (int conf = 1; conf < lim; conf++)
        vrajeala[conf] = __builtin_popcount(conf);
}

/*int popcount(int x) {
    return vrajeala[x >> 17] + vrajeala[x & mask2];
}*/

void back(int pas, int who) {
    if (cnt == a) {
        ans += comb[popcount(who)][b];
        return;
    }

    if (n - pas + 1 > a - cnt)
        back(pas + 1, who);

    cnt++;
    if (popcount(who) >= b)
        back(pas + 1, who & adj[pas]);
    cnt--;
}

int main()
{
    freopen("gbc.in","r",stdin);
    freopen("gbc.out","w",stdout);

    scanf("%d%d%d", &n, &a, &b);
    for (i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        adj[i] = 0;
        for (j = 1; j <= n; j++)
            if (s[j] == '1')
                adj[i] |= 1 << j;
    }

    if (a + b > n) {printf("0"); return 0;}

    if (a > b) swap(a, b);
    pre();

    mask = (1 << (n + 1)) - 2;
    back(1, mask);

    printf("%lld", ans);


    return 0;
}
