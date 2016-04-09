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

#define maxN 30011

int n, m, x, y, i, perfect;

bool us[maxN];

int how_many[maxN];
int min_id[maxN];
int dad[maxN];
int gr[maxN];

int pos;
vector<int> mn, pl;

vector< pair<int, int> > ans;



int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int R1, int R2) {
    R1 = Find(R1);
    R2 = Find(R2);

    if (R1 == R2) return false;
    how_many[R1] += how_many[R2];
    min_id[R1] = min(min_id[R2], min_id[R1]);
    dad[R2] = R1;
    return true;
}




int main()
{
    freopen("turism.in","r",stdin);
    freopen("turism.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) dad[i] = i, min_id[i] = i;

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        Merge(x, y);
        gr[x]++;
        gr[y]--;
    }

    //! add plus and minus
    for (i = 1; i <= n; i++) {
        if (gr[i] > 0) how_many[ Find(i) ] += gr[i];

        while (gr[i] < 0) {
            mn.pb(i);
            gr[i]++;
        }

        while (gr[i] > 0) {
            pl.pb(i);
            gr[i]--;
        }
    }

    //! add perfect components ( + and - in the smallest node )
    for (i = 1; i <= n; i++) {
        if (how_many[ Find(i) ]) continue;
        int R = Find(i);

        if (us[R]) continue;
        us[R] = true;
        pl.pb(min_id[R]);
        mn.pb(min_id[R]);

        perfect++;
        how_many[R] = 1;
    }

    pos = 0;
    sort(pl.begin(), pl.end());
    sort(mn.begin(), mn.end());

    if (pl.empty() && perfect == 1) {
        printf("0");
        return 0;
    }

    //! select the best pl for every mn
    for (int act : mn) {
        int R = Find(act);
        bool deny = (how_many[R] == 1);

        if (pos == (int)pl.size() - 1) deny = false;

        if (Merge(act, pl[pos]) == false && deny) {
            swap(pl[pos], pl[pos + 1]);
            Merge(act, pl[pos]);
        }

        ans.pb(mp(act, pl[pos]));

        R = Find(act);
        how_many[R]--;

        pos++;
    }

    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d %d\n", e.first, e.second);

    return 0;
}
