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

#define maxN 250011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define T pair<int, int>
#define inf 1000000
int lim;

struct event {
    int x, y, cnt;

    bool operator<(const event& who)const {
        return mp(x, y) < mp(who.x, who.y);
    }
};



int n, m, t, i, x, y, cnt, pos, added;
event E[maxN], Q[maxN];
int id[maxN];

int data[maxN];
ll ans[maxN];




bool cmp(int a, int b) {
    return Q[a] < Q[b];
}

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int v) {
    while (pos <= lim) {
        data[pos] += v;
        pos += zrs(pos);
    }
}

int sum(int pos) {
    int ans = 0;
    while (pos) {
        ans += data[pos];
        pos -= zrs(pos);
    }
    return ans;
}



int main()
{
    freopen("galerie.in","r",stdin);
    freopen("galerie.out","w",stdout);

    scanf("%d%d%d", &n, &m, &t);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &cnt);
        if (x > y) swap(x, y);
        E[i] = {x, y, cnt};
    }

    lim = n;
    n = m;
    sort(E + 1, E + n + 1);

    for (i = 1; i <= t; i++) {
        scanf("%d%d%d", &x, &y, &cnt);
        if (x > y) swap(x, y);
        Q[i] = {x, y, cnt};
        id[i] = i;
    }

    sort(id + 1, id + t + 1, cmp);

    pos = 1;
    for (i = 1; i <= t; i++) {
        int act = id[i];

        while (E[pos].x <= Q[act].x && pos <= n) {
            add(E[pos].y, E[pos].cnt);
            added += E[pos++].cnt;
        }

        if (Q[act].cnt >= Q[act].y - Q[act].x) {
            ans[act] = 0;
            continue;
        }

        int how = added - sum(Q[act].y - 1);
        ans[act] = 1LL * how * (Q[act].y - Q[act].x - Q[act].cnt);
    }

    for (i = 1; i <= t; i++)
        printf("%lld\n", ans[i]);


    return 0;
}
