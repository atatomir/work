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

const int maxN = 500011;
const int thre = 700;

class Buffer {
    public:

    private:

};

struct query {
    int l, r, id;

    bool operator<(const query& who)const {
        return mp(l / thre, r) < mp(who.l / thre, who.r);
    }
};

int n, i, l, r, q;
int a[maxN];
query Q[maxN];
int cnt[maxN];
vector<int> cand;
int ans[maxN];
bool in_cand[maxN];

inline void add(int v) {
    if (in_cand[v]) return;
    in_cand[v] = true;
    cand.pb(v);
}

void solve(const query &act) {
    while (act.l < l) {
        l--;
        if (++cnt[a[l]] == 1) add(a[l]);
    }

    while (r < act.r) {
        r++;
        if (++cnt[a[r]] == 1) add(a[r]);
    }

    while (l < act.l) {
        if (--cnt[a[l]] == 1) add(a[l]);
        l++;
    }

    while (r > act.r) {
        if (--cnt[a[r]] == 1) add(a[r]);
        r--;
    }

    while (!cand.empty()) {
        if (cnt[cand.back()] == 1) break;
        in_cand[cand.back()] = false;
        cand.pop_back();
    }

    if (cand.empty()) 
        ans[act.id] = 0;
    else
        ans[act.id] = cand.back();
}

int main()
{
    //freopen("test.in","r",stdin);

    cand.reserve(n);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        scanf("%d%d", &Q[i].l, &Q[i].r);
        Q[i].id = i;
    }

    sort(Q + 1, Q + q + 1);
    l = 1; r = 0;
    for (i = 1; i <= q; i++)
        solve(Q[i]);

    for (i = 1; i <= q; i++) printf("%d\n", ans[i]);

    return 0;
}
