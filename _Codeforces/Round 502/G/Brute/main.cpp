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

const int maxN = 100011;

int n, q, i, x, y;
vector<int> list[maxN];
bool act[maxN];

void add(int node) {
    if (!act[node]) {
        act[node] = true;
        return;
    }

    for (auto to : list[node])
        add(to);
}

void rm(int node) {
    act[node] = false;
    for (auto to : list[node])
        rm(to);
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        list[x].pb(i);
    }

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &x, &y);
        if (x == 1) add(y);
        if (x == 2) rm(y);
        if (x == 3) {
            if (act[y])
                printf("black\n");
            else
                printf("white\n");
        }
    }



    return 0;
}
