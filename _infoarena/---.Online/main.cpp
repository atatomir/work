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

#define maxN 222

struct edge {
    int x, y, c;

    bool operator<(const edge& who) const {
        return c < who.c;
    }
};

int n, m, i, x, y, c;
vector< edge > old, act;
int dad[maxN], smen[maxN];

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;
    if (smen[x] < smen[y])
        dad[x] = y, smen[y]++;
    else
        dad[y] = x, smen[x]++;
    return true;
}

int solve() {
    int i, ans;

    old = act;
    act.clear();
    ans = 0;

    for (i = 1; i <= n; i++) dad[i] = i, smen[i] = 0;
    for (auto e : old) {
        if (Merge(e.x, e.y))
            act.pb(e), ans += e.c;
    }

    return ans;

}

void insr(vector<edge>& v) {
    for (int i = v.size() - 2; i >= 0; i--)
        if (v[i + 1] < v[i])
            swap(v[i], v[i + 1]);
        else
            return;
}

int main()
{
    freopen("online.in","r",stdin);
    freopen("online.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        act.pb({x, y, c});
    }

    sort(act.begin(), act.end());
    printf("%d\n", solve());

    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        act.pb({x, y, c});
        insr(act);

        printf("%d\n", solve());
    }


    return 0;
}
