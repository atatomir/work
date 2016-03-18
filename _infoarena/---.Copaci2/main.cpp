#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1024


int n, i, m, k;
int v[maxN];
int cost[maxN];
int lim;

int ss, dd;
int dp[2][maxN];

int pos;
deque<int> DQ;



int abs(int x) {
    if (x > 0) return x;
    return -x;
}

bool check(int diff) {
    int i, j;

    memset(dp, 0, sizeof(dp));
    ss = 0;
    dd = 1;
    for (i = 1; i <= lim; i++)
        dp[ss][i] = cost[1] * abs(i - v[1]);


    for (i = 2; i <= n; i++) {
        DQ.clear();
        pos = 1;

        int mini = 1000000000;

        for (j = 1; j <= lim; j++) {
            while (pos <= lim && pos <= j + diff) {
                //! we need add a new elem to the dq

                while (!DQ.empty()) {
                    if(dp[ss][ DQ.back() ] < dp[ss][pos]) break;
                    DQ.pop_back();
                }
                DQ.push_back(pos++);
            }

            if (DQ.front() < j - diff) DQ.pop_front();

            dp[dd][j] = dp[ss][ DQ.front() ] + cost[i] * abs(j - v[i]);
            mini = min(mini, dp[dd][j]);
        }

        if (mini > k) return false;

        swap(ss, dd);
    }


    return true;
}


int main()
{
    freopen("copaci2.in","r",stdin);
    freopen("copaci2.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &v[i], &cost[i]);
        lim = max(lim, v[i]);
    }

    int ans = -1;
    for (int step = 512; step; step >>= 1)
        if ( !check(ans + step) )
            ans += step;

    printf("%d", ans + 1);

    return 0;
}
