#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 411
#define maxM 100011

int n, m, i, j, ans;
int x[maxM], y[maxM];

bool good[maxN];
bitset<maxN> need[maxN];

void pre(int node) {
    int i;

    good[node] = true;
    need[node].reset(); need[node][node] = 1;

    for (i = m; i > 0; i--) {
        if (need[node][x[i]] && need[node][y[i]]) {
            good[node] = false;
            return;
        }

        if (!need[node][x[i]] && !need[node][y[i]])
            continue;

        need[node][x[i]] = 1;
        need[node][y[i]] = 1;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++)
        scanf("%d%d", &x[i], &y[i]);

    for (i = 1; i <= n; i++)
        pre(i);

    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            if (good[i] && good[j])
                if ((need[i] & need[j]) == need[0])
                    ans++;

    cout << ans;


    return 0;
}
