#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define maxM 12

int n, k, i, j, cnt;
int dim[maxN];
ll cost[maxN][maxM];
ll base;
vector<int> aux;

ll save;
ll solution;


int bs(int money) {
    int ans, step;

    ans = -1;
    for (step = 1 << 17; step > 0; step >>= 1)
        if (ans + step < aux.size())
            if (cost[aux[ans + step]][2] <= money)
                ans += step;

    return ans + 1;
}

void check(int step, ll money) {
    if (cnt >= k) return;
    if (step == -1) {
        save += money;
        cnt++;
        return;
    }

    if (cost[aux[step]][2] > money)
        step = bs(money);

    if (step == -1) {
        save += money;
        cnt++;
        return;
    }

    check(step - 1, money);
    for (int i = 2; i <= dim[ aux[step] ]; i++) {
        if (money < cost[aux[step]][i]) break;
        check(step - 1, money - cost[aux[step]][i]);
    }
}


int main()
{
    freopen("roboherd.in","r",stdin);
    freopen("roboherd.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &dim[i]);
        for (j = 1; j <= dim[i]; j++) scanf("%lld", &cost[i][j]);
        sort(cost[i] + 1, cost[i] + dim[i] + 1);

        base += cost[i][1];
        for (j = 2; j <= dim[i]; j++) cost[i][j] -= cost[i][1];

        if (dim[i] > 1) aux.pb(i);
    }

    sort(aux.begin(), aux.end(), [](int a, int b)->bool const {
        return cost[a][2] < cost[b][2];
    });

    ll ans = -1;
    for (ll step = 1LL << 40; step > 0; step >>= 1) {
        cnt = 0; save = 0;
        check(aux.size() - 1, ans + step);
        if (cnt < k) ans += step;
    }


    if (ans == -1) {
        solution = base * k;
        printf("%lld", solution);
        return 0;
    }

    cnt = 0; save = 0;
    check(aux.size() - 1, ans);
    solution = (base + ans + 1) * k - save - cnt;

    printf("%lld", solution);




    return 0;
}
