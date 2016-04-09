#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 30011
#define inf 1000000000

int n, m, i, x, y, k, t;
vector<int> list[maxN];
int wl[maxN]; //! win or lose
int must[maxN][2]; //! min / max

vector<int> work;
bool Nargy;



void compute(int node) {
    if (wl[node] != -1) return;
    if (list[node].empty()) {
        wl[node] = 0;
        must[node][0] = must[node][1] = 0;
        return;
    }

    must[node][0] =  inf;
    must[node][1] = -inf;

    wl[node] = 0;
    for (int to : list[node]) {
        compute(to);
        if (wl[to] == 0) wl[node] = 1;
    }

    for (int to : list[node]) {
        if (wl[to] == wl[node]) continue;

        must[node][0] = min(must[node][0], must[to][1] + 1);
        must[node][1] = max(must[node][1], must[to][0] + 1);
    }
}

bool check() {
    int boss = -inf;
    int other = -inf;

    for (int e : work) {
        if (wl[e] == 0) {
            other = max(other, must[e][0]);
        } else {
            boss = max(boss, must[e][1]);
        }
    }

    return boss >= other;
}


int main()
{
    freopen("pioni2.in","r",stdin);
    freopen("pioni2.out","w",stdout);

    scanf("%d%d%d", &t, &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
    }
    for (i = 1; i <= n; i++) wl[i] = -1;
    for (i = 1; i <= n; i++) compute(i);


    for (int ti = 1; ti <= t; ti++) {
        scanf("%d", &k);
        work.resize(k);
        for (i = 0; i < k; i++) scanf("%d", &work[i]);

        Nargy = check();

        if (Nargy)
            printf("Nargy\n");
        else
            printf("Fumeanu\n");
    }


    return 0;
}
