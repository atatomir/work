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

#define maxN 133072

int n, i, j, x, y, cnt;
pair<int, int> P[maxN];
vector<int> xx, yy;

vector<int> list[maxN << 1];
vector< pair<int, int> > E;
vector<int> who;
vector<bool> valid;

vector<int> odd;
vector<int> ord;

int col[maxN];

int how_x[maxN], how_y[maxN];
int ans;




void dfs(int node) {
    while (!list[node].empty()) {
        int id = list[node].back();
        list[node].pop_back();

        if (valid[id] == false) continue;

        valid[id] = false;
        if (E[id].first == node)
            dfs(E[id].second);
        else
            dfs(E[id].first);

        ord.pb(who[id]);
    }
}

int main()
{
    freopen("primar.in","r",stdin);
    freopen("primar.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);
        xx.pb(P[i].first);
        yy.pb(P[i].second);
    }

    sort(xx.begin(), xx.end());
    xx.resize(unique(xx.begin(), xx.end()) - xx.begin());

    sort(yy.begin(), yy.end());
    yy.resize(unique(yy.begin(), yy.end()) - yy.begin());

    for (i = 1; i <= n; i++) {
        x = lower_bound(xx.begin(), xx.end(), P[i].first) - xx.begin() + 1;
        y = lower_bound(yy.begin(), yy.end(), P[i].second) - yy.begin() + 1;

        how_x[x]++; how_y[y]++;
        y += xx.size();

        E.pb(mp(x, y));
        list[x].pb(E.size() - 1);
        list[y].pb(E.size() - 1);

        who.pb(i);
    }
    cnt = xx.size() + yy.size();

    for (i = 1; i <= cnt; i++)
        if (list[i].size() % 2 == 1)
            odd.pb(i);

    for (i = 1; i < odd.size(); i += 2) {
        E.pb(mp(odd[i - 1], odd[i]));
        list[ odd[i - 1] ].pb(E.size() - 1);
        list[ odd[i] ].pb(E.size() - 1);

        who.pb(0);
    }

    valid.resize(E.size());
    for (i = 0; i < valid.size(); i++) valid[i] = true;

    for (i = 1; i <= n; i++) {
        ord.clear();
        dfs(i);

        int dec = 0;
        for (j = 0; j < ord.size(); j++) {
            if (ord[j] != 0) continue;
            dec = j + 1;
            break;
        }

        for (j = 0; j < dec; j++) ord.pb(ord[j]);

        for (j = dec; j < ord.size(); j++)
            col[ord[j]] = j % 2;
    }

    for (i = 1; i <= xx.size(); i++) {
        if (how_x[i] == 1) continue;
        ans += how_x[i] % 2;
    }

    for (i = 1; i <= yy.size(); i++) {
        if (how_y[i] == 1) continue;
        ans += how_y[i] % 2;
    }

    printf("%d\n", ans);
    for (i = 1; i <= n; i++) printf("%d ", col[i]);


    return 0;
}
