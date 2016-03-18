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

#define maxN 100011

int n, s, t, i;
int cost[maxN];
int need[maxN];

deque<int> DQ;
ll ans;

int main()
{
    freopen("branza.in","r",stdin);
    freopen("branza.out","w",stdout);

    scanf("%d%d%d", &n, &s, &t);

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &cost[i], &need[i]);

        while (!DQ.empty()) {
            if (cost[i] > cost[ DQ.back() ] + s * (i - DQ.back())) break;
            DQ.pop_back();
        }
        DQ.push_back(i);

        if(DQ.front() < i - t) DQ.pop_front();
        ans += 1LL * need[i] * (1LL * cost[ DQ.front() ] + 1LL * (i - DQ.front()) * s);
    }

    printf("%lld", ans);


    return 0;
}
