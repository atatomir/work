#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int n, k, i, j;
ll S, v[maxN];

int ss, dd;
ll dp[2][maxN];

int ql, qr;
int work[maxN];

ll get_cost(int l, int r) {
    return dp[ss][l - 1] + abs(S - v[r] + v[l - 1]);
}

int main()
{
    freopen("secvbest.in","r",stdin);
    freopen("secvbest.out","w",stdout);

    scanf("%d%d%lld", &n, &k, &S);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
        v[i] += v[i - 1];
    }

    ss = 0; dd = 1;
    for (i = 1; i <= n; i++) dp[ss][i] = abs(S - v[i]);
    printf("%lld ", dp[ss][n]);

    for (i = 2; i <= k; i++) {
        ql = 1; qr = 0;
        dp[dd][i] = get_cost(i, i);
        work[++qr] = i;

        for (j = i + 1; j <= n; j++) {
            while (ql <= qr) {
                int last = work[qr];

                if (get_cost(last, j) < get_cost(j, j)) break;
                qr--;
            }

            work[++qr] = j;

            while (qr - ql + 1 >= 2)
                if (get_cost(work[ql], j) >= get_cost(work[ql + 1], j))
                    ql++;
                else
                    break;

            dp[dd][j] = get_cost(work[ql], j);
        }

        printf("%lld ", dp[dd][n]);
        swap(ss, dd);
    }


    return 0;
}
