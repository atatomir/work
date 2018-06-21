#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 2018;

struct interv {
    int other;
    function<void()> same, dif;
};

int n, m, i, x, y;
vector<int> list[maxN];
int a[maxN], b[maxN];

function<void()> nothing, rev;
vector<interv> data[maxN];
int us[maxN];

void dfs(int node, int root) {
    for (auto to : list[node])
        if (to != root)
            dfs(to, node);

    us[node] = true;
    int i;
    for (i = 0; i < data[node].size(); i++) {
        if (us[data[node][i].other]) {
            if (data[node][i].other == node)
                data[node][i].same();

            data[node][i] = data[i].back();
            data[node].pop_back();
            i--;
            continue;
        }
    }

    while (data[node].size() > 2) {
        auto a = data[node].back();
        data[node].pop_back();
        auto b = data[node].back();
        data[node].pop_back();

        auto ab = [a, b]()->void {
            a.dif();
            b.same();
        }; 

        auto ba = [a, b]()->void {
            a.same();
            b.dif();
        };

        data[a.other].pb({b.other, ab, ba});
        data[b.other].pb({a.other, ba, ab});
    }

    if (data[node].size() == 1) {
        auto a = data[node][0];

        data[root].pb({a.other, a.same, a.dif});
        data[a.other].pb({root, a.dif, a.same});
    }
    data[node].clear();
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    nothing = []()->void {};
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &a[i], &b[i]);
        rev = [i]()->void {
            swap(a[i], b[i]);
        };

        data[a[i]].pb({b[i], nothing, rev});
        data[b[i]].pb({a[i], rev, nothing});
    }

    dfs(1, 0);

    for (i = 1; i <= m; i++)
        printf("%d %d\n", a[i], b[i]);

    return 0;
}
