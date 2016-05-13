#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2016
#define maxM 100011
#define mpp(x,y,z) mp(x, mp(y, z))
#define eps 0.00001

struct Ball {
    ll x, y, r;

    void read() {
        scanf("%lld%lld%lld", &x, &y, &r);
    }
};

struct Pupil {
    ll r;
    int id, corner;

    void read(int _id) {
        scanf("%lld%d", &r, &corner);
        id = _id;
    }

    bool operator<(const Pupil& who)const {
        return r < who.r;
    }
};

int n, m, i, j, pos;
ll w, h;
Ball B[maxN];
Pupil P[maxM];
string ans[maxM];

vector< pair<double, pair<int, int> > > adds;

int dad[maxN];

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

void Merge(int R1, int R2) {
    R1 = Find(R1);
    R2 = Find(R2);
    dad[R1] = R2;
}

double dist(int id1, int id2) {
    return sqrt(1.00 * (B[id1].x - B[id2].x) * (B[id1].x - B[id2].x) +
                1.00 * (B[id1].y - B[id2].y) * (B[id1].y - B[id2].y)) ;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    scanf("%lld%lld", &w, &h);
    for (i = 1; i <= n; i++) B[i].read();
    for (i = 1; i <= m; i++) P[i].read(i);

    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            adds.pb(mpp( dist(i, j) - B[i].r - B[j].r, i, j));

    for (i = 1; i <= n; i++) {
        adds.pb(mpp(B[i].x - B[i].r, i, n + 1));
        adds.pb(mpp(B[i].y - B[i].r, i, n + 2));
        adds.pb(mpp(w - B[i].x - B[i].r, i, n + 3));
        adds.pb(mpp(h - B[i].y - B[i].r, i, n + 4));
    }

    sort(adds.begin(), adds.end());
    sort(P + 1, P + m + 1);

    for (i = 1; i <= n + 4; i++) dad[i] = i;

    pos = 0;
    for (i = 1; i <= m; i++) {
        auto act = P[i];

        while (pos < adds.size()) {
            auto cand = adds[pos];

            if (0.50 * cand.first >= 1.00 * act.r - eps) break;
            Merge(cand.second.first, cand.second.second);
            pos++;
        }

        bool deny_one = (Find(n + 1) == Find(n + 2));
        bool deny_two = (Find(n + 2) == Find(n + 3));
        bool deny_three = (Find(n + 3) == Find(n + 4));
        bool deny_four = (Find(n + 4) == Find(n + 1));
        bool deny_hori = (Find(n + 1) == Find(n + 3));
        bool deny_vert = (Find(n + 2) == Find(n + 4));

        if (act.corner == 1) {
            ans[act.id] += '1';
            if (!deny_one && !deny_vert && !deny_two) ans[act.id] += '2';
            if (!deny_one && !deny_vert && !deny_hori && !deny_three) ans[act.id] += '3';
            if (!deny_one && !deny_hori && !deny_four) ans[act.id] += '4';
        }

        if (act.corner == 2) {
            if (!deny_two && !deny_vert && !deny_one) ans[act.id] += '1';
            ans[act.id] += '2';
            if (!deny_two && !deny_hori && !deny_three) ans[act.id] += '3';
            if (!deny_two && !deny_vert && !deny_hori && !deny_four) ans[act.id] += '4';
        }

        if (act.corner == 3) {
            if (!deny_three && !deny_vert && !deny_hori && !deny_one) ans[act.id] += '1';
            if (!deny_three && !deny_hori && !deny_two) ans[act.id] += '2';
            ans[act.id] += '3';
            if (!deny_three && !deny_vert && !deny_four) ans[act.id] += '4';
        }

        if (act.corner == 4) {
            if (!deny_four && !deny_hori && !deny_one) ans[act.id] += '1';
            if (!deny_four && !deny_hori && !deny_vert && !deny_two) ans[act.id] += '2';
            if (!deny_four && !deny_vert && !deny_three) ans[act.id] += '3';
            ans[act.id] += '4';
        }
    }

    for (i = 1; i <= m; i++) {
        ans[i] += '\0';
        printf("%s\n", &ans[i][0]);
    }


    return 0;
}
