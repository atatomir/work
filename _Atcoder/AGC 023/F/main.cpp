#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 200011;

struct group {
    int c0, c1, id;

    bool operator<(const group& who)const {
        return 1LL * c0 * who.c1 < 1LL * c1 * who.c0;
    }
};

int n, i, x, aux;
int p[maxN], dad[maxN];
int cnt0[maxN], cnt1[maxN];
priority_queue<group> H;
ll ans;

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 2; i <= n; i++) scanf("%d", &p[i]);
    for (i = 1; i <= n; i++) {
        dad[i] = i;
        scanf("%d", &x);
        if (x == 0) cnt0[i] = 1;
        else        cnt1[i] = 1;

        if (i != 1)
            H.push({cnt0[i], cnt1[i], i});
    }

    while (!H.empty()) {
        auto act = H.top();
        H.pop();

        if (dad[act.id] != act.id) continue;
        if (act.id == 1) continue;
        if (cnt0[act.id] != act.c0) continue;
        if (cnt1[act.id] != act.c1) continue;

        aux = Find(p[act.id]);
        dad[act.id] = aux;
        ans += 1LL * cnt1[aux] * cnt0[act.id];

        cnt0[aux] += cnt0[act.id];
        cnt1[aux] += cnt1[act.id];
        if (aux != 1)
            H.push({cnt0[aux], cnt1[aux], aux});
    }

    printf("%lld", ans);


    return 0;
}
