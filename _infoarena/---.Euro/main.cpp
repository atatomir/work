#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 35111
#define inf 1e18

int n, i;
long long t;
long long dp[maxN];
long long sum[maxN];

double _time[maxN];
int work[maxN];
int qL, qR;

double getTime(int j1, int j2) {
    double b = dp[j1] - dp[j2];
    double a = sum[j2] - sum[j1];

    if (a == 0)
        if (b > 0)
            return inf;
        else
            return -inf;
    if (a < 0)
        return -b  / a;
    return inf;
}

int main()
{
    freopen("euro.in","r",stdin);
    freopen("euro.out","w",stdout);

    scanf("%d%lld", &n, &t);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &sum[i]);
        sum[i] += sum[i - 1];
    }

    qL = qR = 1;
    work[1] = 0;
    _time[0] = -inf;

    for (i = 1; i <= n; i++) {
        while (qR - qL + 1 > 1 && _time[ work[qL + 1] ] <= i) qL++;

        int prov = work[qL];
        dp[i] = dp[prov] - t + (sum[i] - sum[prov]) * i;

        while (qR - qL + 1 > 1 && getTime(work[qR], i) <= _time[ work[qR] ]) qR--;
        _time[i] = getTime(work[qR], i);
        work[++qR] = i;
    }

    printf("%lld", dp[n]);

    return 0;
}
