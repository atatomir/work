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

#define maxN 2000011

int n, m, i, x, y;
vector< pair<int, int> > pos;
pair<int, int> wh[maxN];
queue<int> Q;

int to[maxN];
bool us[maxN];

int cnt;
vector<int> cic;

int ans;


void bfs(int node) {
    for (; !us[node] && node != 0; node = to[node]) {
        cnt++;
        us[node] = true;
    }
}


int main()
{
    freopen("test.in","r",stdin);

    pos.pb(mp(-1, -1));

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        pos.pb(mp(x, i));
        pos.pb(mp(y, i));
    }

    sort(pos.begin(), pos.end());
    for (i = 1; i < pos.size(); i++) {
        int id = pos[i].second;
        if (wh[id].first == 0)
            wh[id].first = i;
        else
            wh[id].second = i;
    }

    n *= 2;
    for (i = 1; i <= n; i++) {
        int id = pos[i].second;

        if (i == wh[id].first)
            to[i] = 1 + wh[id].second;
        else
            to[i] = 1 + wh[id].first;

        if (to[i] > n) to[i] = 0;
    }

    cnt = 0;
    bfs(1);
    ans = cnt;

    for (i = 2; i <= n; i++) {
        if (us[i]) continue;

        cnt = 0;
        bfs(i);
        cic.pb(cnt);
    }

    sort(cic.begin(), cic.end());
    while (m && !cic.empty()) {
        ans += cic.back() + 2;
        m--; cic.pop_back();
    }

    ans += 4 * (m / 2);
    ans += m & 1;

    printf("%d", ans);


    return 0;
}
