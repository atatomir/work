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

#define maxN 100011

struct node{
    int cnt, id;
    node *from, *to;

    node() {
        cnt = 0;
        from = to = NULL;
        id = 0;
    }

    bool is_good() {
        if (cnt) return false;

        return from->cnt || to->cnt;
    }

};

int n, i, k, x, kk;
int need[maxN];
node *work[maxN];
set<int> good;

vector<int> sol[maxN];
bool valid[maxN];

void update(node *act) {
    if (good.find(act->id) != good.end())
        good.erase(act->id);

    if (act->is_good())
        good.insert(act->id);
}

int main()
{
    freopen("romania.in","r",stdin);
    freopen("romania.out","w",stdout);

    scanf("%d%d", &n, &k);
    kk = k;

    for (i = 1; i <= n; i++)
        work[i] = new node();

    for (i = 1; i <= n; i++) {
        work[i]->id = i;
        valid[i] = true;

        if (i != 1) work[i]->from = work[i - 1];
        if (i != n) work[i]->to = work[i + 1];
    }
    work[1]->from = work[n];
    work[n]->to = work[1];

    for (i = 1; i <= k; i++) {
        scanf("%d", &x);
        work[x]->cnt++;
        need[i] = x;
    }

    if (k > n - 3) {
        printf("-1");
        return 0;
    }

    for (i = 1; i <= n; i++)
        if(work[i]->is_good())
            good.insert(i);

    for (; k > 0; k--) {
        int v = *good.begin();
        good.erase(v);
        valid[v] = false;

        auto ff = work[v]->from;
        auto now = work[v];
        auto tt = work[v]->to;

        if (ff->cnt) {
            ff->cnt--;
            sol[ff->id].pb(tt->id);
        } else {
            tt->cnt--;
            sol[tt->id].pb(ff->id);
        }

        ff->to = tt;
        tt->from = ff;

        update(ff->from);
        update(ff);
        update(tt);
        update(tt->to);
    }

    for (i = 1; i <= kk; i++) {
        int to = sol[ need[i] ][ sol[need[i]].size() - 1 ];
        sol[need[i]].pop_back();

        printf("%d %d\n", need[i], to);
    }


    return 0;
}
