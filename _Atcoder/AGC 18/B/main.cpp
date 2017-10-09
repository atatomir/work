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

int n, m, i, j, ans;
int ord[maxN][maxN], pos[maxN];
bool dead[maxN];

int cnt[maxN];

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> m; ans = n;
    for (i = 1; i <= n; i++) {
        pos[i] = 1;
        for (j = 1; j <= m; j++) cin >> ord[i][j];
    }

    for (int step = 1; step < m; step++) {
        for (i = 1; i <= m; i++) cnt[i] = 0;
        for (i = 1; i <= n; i++) {
            while (dead[ord[i][ pos[i] ]]) pos[i]++;
            cnt[ord[i][ pos[i] ]]++;
        }

        int bg = 1;
        for (i = 1; i <= m; i++)
            if (cnt[i] > cnt[bg])
                bg = i;

        ans = min(ans, cnt[bg]);
        dead[bg] = true;
    }

    cout << ans;


    return 0;
}
