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

#define maxN 100011
#define inf (2000800001)

struct intr {
    int l, r, cost;
};

int n, i, last;
intr I[maxN];
pair<int, int> ans = mp(-inf, 0);

vector<int> from_left, from_right;



bool cmp1(const intr& a, const intr& b) {
    return a.r < b.r;
}

bool cmp2(const intr& a, const intr& b) {
    return a.l > b.l;
}

int how_many(const intr& act) {
    int p1 = lower_bound(from_left.begin(), from_left.end(), act.l) - from_left.begin();
    int p2 = upper_bound(from_right.begin(), from_right.end(), act.r) - from_right.begin();

    return p1 + from_right.size() - p2 + 1;
}

int main()
{
    freopen("troll.in","r",stdin);
    freopen("troll.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d%d%d", &I[i].l, &I[i].r, &I[i].cost);

    last = -1;
    sort(I + 1, I + n + 1, cmp1);
    for (i = 1; i <= n; i++) {
        if (I[i].l <= last) continue;
        last = I[i].r;
        from_left.pb(last);
    }

    last = inf;
    sort(I + 1, I + n + 1, cmp2);
    for (i = 1; i <= n; i++) {
        if (I[i].r >= last) continue;
        last = I[i].l;
        from_right.pb(last);
    }
    reverse(from_right.begin(), from_right.end());

    for (i = 1; i <= n; i++) {
        if (I[i].cost < ans.first) continue;
        ans = max(ans, mp(I[i].cost, how_many(I[i])));
    }

    printf("%d %d", ans.first, ans.second);


    return 0;
}
