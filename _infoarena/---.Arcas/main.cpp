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

#define maxN 400011
#define pii pair<int, int>
#define def 100000

struct target {
    int x, y1, y2;

    void read() {
        scanf("%d%d%d", &x, &y1, &y2);
        y1 -= x;
        y2 -= x;

        y1 += def;
        y2 += def;
    }
};

struct arrow {
    int x1, x2, y;

    void read() {
        scanf("%d%d%d", &x1, &y, &x2);
        x2 += x1;
        y -= x1;

        y += def;
    }
};

int n, m, i, pos;
target T[maxN];
arrow A[maxN];
vector< pii > ev_T;
vector< pii > ev_A;
int ans[maxN];

int aib[maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

int sum(int pos) {
    int ans = 0;

    while (pos) {
        ans += aib[pos];
        pos -= zrs(pos);
    }

    return ans;
}

void add(int pos, int val) {
    while (pos <= 2 * def) {
        aib[pos] += val;
        pos += zrs(pos);
    }
}


int main()
{
    freopen("arcas.in","r",stdin);
    freopen("arcas.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        T[i].read();
        ev_T.pb(mp(T[i].x, i));
    }

    for (i = 1; i <= m; i++) {
        A[i].read();
        ev_A.pb(mp(A[i].x1 - 1, -i));
        ev_A.pb(mp(A[i].x2, +i));
    }

    sort(ev_T.begin(), ev_T.end());
    sort(ev_A.begin(), ev_A.end());

    pos = 0;
    for (auto e : ev_A) {
        int act_time = e.first;
        int id = e.second;

        while (pos < ev_T.size()) {
            if (ev_T[pos].first > act_time) break;
            int t_id = ev_T[pos++].second;

            add(T[t_id].y1, +1);
            add(T[t_id].y2 + 1, -1);
        }

        if (id < 0)
            ans[-id] -= sum(A[-id].y);
        else
            ans[id] += sum(A[id].y);
    }

    for (i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
