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

int n, k, i, j, x;
int a[maxN], sum;
int act[maxN];
ll up, down;

priority_queue< pair<int, int> > unable, enable;

void result(int x) {
    printf("%d", x);
    exit(0);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    for (i = 1; i <= k; i++) {
        scanf("%d", &x);
        act[x]++;
    }

    //! remove complete groups
    int times = 2000000000;
    for (i = 1; i <= n; i++) times = min(times, act[i] / a[i]);

    k = 0;
    for (i = 1; i <= n; i++) act[i] -= a[i] * times, k += act[i];

    //! add actual group
    for (i = 1; i <= n; i++) {
        for (j = act[i] + 1; j <= a[i]; j++) {
            up = sum * (j - 1);
            down = a[i];

            if (up % down == 0) up += down;
            unable.push(mp( -(up / down), i ));
        }
    }

    for (i = k + 1; i <= sum; i++) {
        while (!unable.empty()) {
            auto now = unable.top();
            if (-now.first > i) break;
            unable.pop();

            int id = now.second;
            int cnt = ++act[id];

            up = 1LL * sum * (cnt - 1 + 1);
            down = a[id];

            if (up % down == 0) up -= down;
            enable.push(mp( -(up / down) - 1, id ));
        }

        if (enable.empty()) result(i - k - 1);
        if (-enable.top().first < i) result(i - k - 2);
        enable.pop();
    }

    printf("forever");

    return 0;
}
