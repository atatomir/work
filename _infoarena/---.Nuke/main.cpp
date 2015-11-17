#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxM 100011
#define maxN maxM * 2
#define eps 1e18
#define ll long long

struct Bomb {
    int x, y, R;

    void read() {
        scanf("%d%d%d", &x, &y, &R);
    }
};

int n, m, i, x, y, r, ans;
pair<int, int> S[maxN];
Bomb B[maxM];

vector< pair<int, int> > Events;
vector< int > s_id;

set< pair<int, int> > work;
int killedBy[maxN];

//! in decreasing order
//! swap from right to left
bool cmp(int x, int y) {
    return S[x].first > S[y].first;
}

bool isIn(int id, ll x, ll y) {
    ll xx = B[id].x;
    ll yy = B[id].y;

    bool aux = 1LL* B[id].R * B[id].R >= (x - xx) * (x - xx) + (y - yy) * (y - yy);

    if (aux) killedBy[id]++;
    return aux;
}

bool found(int x, int y) {
    int c1, c2;

    if (work.empty()) return false;

    auto it = work.lower_bound(mp(y, 0));

    if (it == work.begin()) {
        c1 = c2 = it->second;
    }
    else
    if (it == work.end()) {
        it--;
        c1 = c2 = it->second;
    }
    else {
        c2 = it->second;
        it--;
        c1 = it->second;
    }

    if (isIn(c1, x, y))
        return true;
    if (isIn(c2, x, y))
        return true;
    return false;
}

int main()
{
    freopen("nuke.in","r",stdin);
    freopen("nuke.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d%d", &S[i].first, &S[i].second);
    for (i = 1; i <= m; i++) {
        B[i].read();
        Events.pb(mp(B[i].x - B[i].R - 1, -i));
        Events.pb(mp(B[i].x + B[i].R, +i));
    }

    sort(Events.begin(), Events.end());

    s_id.resize(n);
    for (i = 0; i < n; i++) s_id[i] = i + 1;
    sort(s_id.begin(), s_id.end(), cmp);

    work.clear();
    for (auto id : s_id) {
        int xx = S[id].first;
        int yy = S[id].second;

        while (!Events.empty()) {
            auto last = Events[ Events.size() - 1 ];
            if (last.first < xx) break;

            if (last.second > 0)
                work.insert(mp(B[last.second].y, last.second));
            else
                work.erase(mp(B[-last.second].y, -last.second));

            Events.pop_back();
        }

        if (found(xx, yy)) ans++;
    }

    for (i = 1; i <= m; i++) printf("%d\n", killedBy[i]);
    //cerr << ans;

    return 0;
}
