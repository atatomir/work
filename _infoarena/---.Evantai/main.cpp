#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 711
#define mod 30103
#define norm(x) if (x >= mod) x -= mod;

int n, i, j;
int v[maxN];
vector< pair<int, int> > pos;

int ans;
int aib[maxN][maxN];
int ind = 0;
int help[maxN * maxN];

int zrs(int x) {
    return (x & (x - 1)) ^ x;
}

/*void norm(int &x) {
    if (x >= mod) x -= mod;
}*/

int add_aib(int x, int y, int v) {
    int _y = y;
    while (x <= n) {
        y = _y;
        while (y <= n) {
            aib[x][y] += v;
            norm(aib[x][y]);
            y += zrs(y);
        }
        x += zrs(x);
    }
}

int sum_aib(int x, int y) {
    int _y = y;
    int ans = 0;

    while (x > 0) {
        y = _y;

        while (y > 0) {
            ans += aib[x][y];
            norm(ans);

            y -= zrs(y);
        }

        x -= zrs(x);
    }

    return ans;
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return v[a.first] + v[a.second] < v[b.first] + v[b.second];
}

int main()
{
    freopen("evantai.in","r",stdin);
    freopen("evantai.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    for (i = 1; i < n; i++)
        for (j = i + 1; j <= n; j++) pos.pb(mp(i, j));

    sort(pos.begin(), pos.end(), cmp);

    while (ind < pos.size()) {
        int targ = v[ pos[ind].first ] + v[ pos[ind].second ];

        for (i = ind; i < pos.size(); i++) {
            int how = v[ pos[i].first ] + v[ pos[i].second ];
            if (how != targ) break;

            help[i] = 1 + sum_aib(n, pos[i].second - 1) - sum_aib(pos[i].first, pos[i].second - 1);
            while (help[i] < 0) help[i] += mod;
            norm(help[i]);
        }

        for (; ind < pos.size(); ind++) {
            int how = v[ pos[ind].first ] + v[ pos[ind].second ];
            if (how != targ) break;

            add_aib(pos[ind].first, pos[ind].second, help[ind]);
            ans += help[ind];
            norm(ans);
        }
    }

    printf("%d", ans);
    cerr << "Answer " << ans << '\n';


    return 0;
}
