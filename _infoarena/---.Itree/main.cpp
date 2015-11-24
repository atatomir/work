#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxN 100011

int n, i, t, x, y;
int gr[maxN];
vector<int> list[maxN];

bool valid() {
    int i;
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        gr[i] = 0;
        list[i].clear();
    }

    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
        gr[x]++; gr[y]++;
    }

    for (i = 1; i <= n; i++) {
        int how = 0;
        for (int j = 0; j < list[i].size(); j++)
            if (gr[ list[i][j] ] > 1)
                how++;

        if (how >= 3)
            return false;
    }

    return true;
}

int main()
{
    freopen("itree.in", "r", stdin);
    freopen("itree.out", "w", stdout);

    scanf("%d", &t);
    for (i = 1; i <= t; i++) {
        if (valid())
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
