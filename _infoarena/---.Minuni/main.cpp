#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int m, n, i, id, dad_id;
pair<int, int> adds[maxN];
vector< pair<int, int> > intr;

stack< pair<int, int> > S;
int dad[maxN], new_dad[maxN];
ll ans[maxN];

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

void kill(int x) {
    dad[x] = new_dad[x];
}

ll get_ans(pair<int, int> me, pair<int, int> you) {
    ll delta_x = me.first - you.first;
    ll delta_y = you.second - me.second;
    ll ans = delta_y * me.first + delta_x * (m - me.second + 1) - delta_x * delta_y;

    return ans;
}

int main()
{
    freopen("minuni.in","r",stdin);
    freopen("minuni.out","w",stdout);

    scanf("%d%d", &m, &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &adds[i].first, &adds[i].second);
        intr.pb(adds[i]);
    }

    intr.pb(mp(0, m + 1));
    sort(intr.begin(), intr.end());

    for (i = 0; i <= n; i++) dad[i] = new_dad[i] = i;
    S.push(mp(m + 1, 0));

    for (i = 1; i < intr.size(); i++) {
        while (S.top().first < intr[i].second) S.pop();
        new_dad[i] = S.top().second;
        S.push(mp(intr[i].second, i));
    }

    for (i = n; i > 0; i--) {
        auto act = adds[i];
        id = lower_bound(intr.begin(), intr.end(), act) - intr.begin();

        kill(id);
        dad_id = Find(id);

        ans[i] = get_ans(intr[id], intr[dad_id]);
    }

    for (i = 1; i <= n; i++) printf("%lld\n", ans[i]);

    return 0;
}
