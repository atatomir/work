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
#define inf 2000000000

int n, k, i, j, last, cnt, id;
pair<int, int> P[maxN];

vector< pair<int, int> > E, loc, aux1, aux2;
bool in_use[maxN];
vector<int> act;

ll ans[maxN];



void solve(ll dim) {
    int i, j;
    int sum;

    aux2 = aux1;
    for (i = 0; i < aux2.size(); i++) aux2[i].first += k, aux2[i].second = -1;
    loc.resize(aux1.size() + aux2.size());
    merge(aux1.begin(), aux1.end(), aux2.begin(), aux2.end(), loc.begin());

    sum = 0;
    for (i = 0; i < loc.size(); i = j) {
        if (i != 0)
            ans[sum] += 1LL * (loc[i].first - loc[i - 1].first) * dim;

        for (j = i; j < loc.size(); j++) {
            if (loc[i].first != loc[j].first) break;
            sum += loc[j].second;
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);
        E.pb(mp(P[i].second, +i));
        E.pb(mp(P[i].second + k, -i));
    }

    sort(E.begin(), E.end());
    last = -inf;

    for (i = 0; i < E.size(); i = j) {
        //! clean up and build events
        cnt = 0; aux1.clear();
        for (j = 0; j < act.size(); j++) {
            if (in_use[ act[j] ] == false) continue;
            act[cnt++] = act[j];

            id = act[j];
            aux1.pb(mp(P[id].first, +1));
        }
        act.resize(cnt);
        sort(aux1.begin(), aux1.end());

        //! solve
        solve(E[i].first - last);
        last = E[i].first;

        //! compute next state
        for (j = i; j < E.size(); j++) {
            if (E[i].first != E[j].first) break;

            int id = abs(E[j].second);
            if (E[j].second > 0) {
                in_use[id] = true;
                act.pb(id);
            } else {
                in_use[id] = false;
            }
        }
    }

    for (i = 1; i <= n; i++) printf("%lld ", ans[i]);

    return 0;
}
