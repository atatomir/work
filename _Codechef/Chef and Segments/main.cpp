#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1024

int t, ti;
int n, i, j;
int a[maxN];

vector<int> norm;
map<int, int> tr;
vector<int> pos[maxN];

ll ans, act;
ll pre[maxN];
set< pair<int, int> > S;

void readd(int l, int r) {
    if (l <= r) {
        S.insert(mp(l, r));
        act += pre[r - l + 1];
    }
}

void rm_element(int pos) {
    auto it = S.lower_bound(mp(pos + 1, 0));
    if (it == S.begin()) return;
    it--;

    if (pos > it->second) return;
    act -= pre[it->second - it->first + 1];
    readd(it->first, pos - 1);
    readd(pos + 1, it->second);

    S.erase(it);
}

int main()
{
    //freopen("test.in","r",stdin);

    for (i = 1; i < maxN; i++)
        pre[i] = (1LL * i * (i + 1)) / 2;

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        norm.clear();

        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            norm.pb(a[i]);
            pos[i].clear();
        }

        sort(norm.begin(), norm.end());
        norm.resize(unique(norm.begin(), norm.end()) - norm.begin());
        for (i = 0; i < norm.size(); i++)
            tr[norm[i]] = i + 1;

        for (i = 1; i <= n; i++) {
            a[i] = tr[a[i]];
            pos[ a[i] ].pb(i);
        }

        ans = 0;

        for (i = 1; i <= n; i++) {
            S.clear();
            act = pre[n - i];
            S.insert(mp(i + 1, n));

            for (j = i; j < n && act != 0; j++) {
                for (auto e : pos[a[j]])
                    rm_element(e);

                ans += act;
            }
        }

        printf("%lld\n", ans);
    }


    return 0;
}
