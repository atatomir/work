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

#define maxN 333

int n, i, j, k;
int dist[maxN][maxN];
bool any;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            cin >> dist[i][j];

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            any = false;

            for (k = 1; k <= n; k++) {
                if (k == i || k == j) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    cout << -1;
                    return 0;
                }

                if (dist[i][j] == dist[i][k] + dist[k][j])
                    any = true;
            }

            if (!any) ans += 1LL * dist[i][j];
        }
    }

    cout << ans;


    return 0;
}
