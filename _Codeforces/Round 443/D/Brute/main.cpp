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

#define maxN 1111
#define maxK 14
#define maxQ 1111

int n, k, q, i, j, tp, x, y, cnt;
int data[maxQ][maxN];

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    cin >> n >> k >> q; cnt = k;
    for (i = 1; i <= k; i++)
        for (j = 1; j <= n; j++)
            cin >> data[i][j];

    for (int qq = 1; qq <= q; qq++) {
        cin >> tp >> x >> y;

        if (tp == 1) {
            cnt++;
            for (i = 1; i <= n; i++)
                data[cnt][i] = max(data[x][i], data[y][i]);
        }

        if (tp == 2) {
            cnt++;
            for (i = 1; i <= n; i++)
                data[cnt][i] = min(data[x][i], data[y][i]);
        }

        if (tp == 3)
            cout << data[x][y] << '\n';
    }


    return 0;
}
