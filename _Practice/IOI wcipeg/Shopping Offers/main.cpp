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
#define pii pair<int, int>

#define maxM 7
#define inf 1000000000

int nor[1024];

struct offer {
    vector< pii > prods;
    int price;

    void read() {
        int n, i, a, b;

        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%d%d", &a, &b);
            prods.pb(mp(a, b));
        }
        scanf("%d", &price);
    }

    void norm() {
        for (int i = 0; i < prods.size(); i++)
            prods[i].first = nor[ prods[i].first ];
    }
};

int n, m, i, x;
int need[maxM];
int dp[maxM][maxM][maxM][maxM][maxM];

offer work[111];
int price[maxM];

int i1, i2, i3, i4, i5;
int j[maxM];
int ans;

int compute_to_final(int i1, int i2, int i3, int i4, int i5) {
    int v = price[1] * (need[1] - i1) +
            price[2] * (need[2] - i2) +
            price[3] * (need[3] - i3) +
            price[4] * (need[4] - i4) +
            price[5] * (need[5] - i5) ;
    return v;
}

bool get_new_index(int id) {
    j[1] = i1;
    j[2] = i2;
    j[3] = i3;
    j[4] = i4;
    j[5] = i5;

    for (auto e : work[id].prods) {
        j[ e.first ] -= e.second;
        if (j[e.first] < 0) return false;
    }

    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) work[i].read();
    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d", &x);
        nor[x] = i;
        scanf("%d%d", &need[i], &price[i]);
    }

    for (i = 1; i <= n; i++) work[i].norm();

    for (i1 = 0; i1 <= need[1]; i1++)
        for (i2 = 0; i2 <= need[2]; i2++)
            for (i3 = 0; i3 <= need[3]; i3++)
                for (i4 = 0; i4 <= need[4]; i4++)
                    for (i5 = 0; i5 <= need[5]; i5++)
                        dp[i1][i2][i3][i4][i5] = inf;

    dp[0][0][0][0][0] = 0;
    ans = compute_to_final(0, 0, 0, 0, 0);

    for (i1 = 0; i1 <= need[1]; i1++)
        for (i2 = 0; i2 <= need[2]; i2++)
            for (i3 = 0; i3 <= need[3]; i3++)
                for (i4 = 0; i4 <= need[4]; i4++)
                    for (i5 = 0; i5 <= need[5]; i5++) {

                        for (i = 1; i <= n; i++) {
                            if(get_new_index(i) == false) continue;
                            dp[i1][i2][i3][i4][i5] = min(dp[i1][i2][i3][i4][i5],
                                                         dp[j[1]][j[2]][j[3]][j[4]][j[5]] + work[i].price);
                        }

                        ans = min(ans, compute_to_final(i1, i2, i3, i4, i5) + dp[i1][i2][i3][i4][i5]);
                    }

    printf("%d", ans);


    return 0;
}
