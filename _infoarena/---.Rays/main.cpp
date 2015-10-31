#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 200011
#define eps 1e-17

int n, i;
pair<int, pair<int, int> > P[maxN];
int ans = 0;

vector< pair<double, int> > Events;
vector<int> aux;
bool us[maxN];

void compute() {
    int i;
    memset(us, 0, sizeof(us));

    for (auto e : Events) {
        if (e.second > 0) {
            aux.pb(e.second);
        } else {
            if (us[-e.second]) continue;

            ans++;
            for (auto who : aux) us[who] = true;
            aux.clear();
        }
    }
}

int main()
{
    freopen("rays.in","r",stdin);
    freopen("rays.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d%d", &P[i].first, &P[i].second.first, &P[i].second.second);

    Events.clear();
    for (i = 1; i <= n; i++) {
        if (P[i].first < 0) {
            double tg1 = (1.00 * P[i].second.first) / P[i].first;
            double tg2 = (1.00 * P[i].second.second) / P[i].first;
            if (tg1 > tg2) swap(tg1, tg2);

            Events.pb(mp(tg1 - eps, +i));
            Events.pb(mp(tg2 + eps, -i));
        }
    }
    sort(Events.begin(), Events.end());

    compute();

    //!----------------------

    Events.clear();
    for (i = 1; i <= n; i++) {
        if (P[i].first > 0) {
            double tg1 = 1.00 * P[i].second.first / P[i].first;
            double tg2 = 1.00 * P[i].second.second / P[i].first;
            if (tg1 > tg2) swap(tg1, tg2);

            Events.pb(mp(tg1 - eps, +i));
            Events.pb(mp(tg2 + eps, -i));
        }
    }
    sort(Events.begin(), Events.end());

    compute();

    //!---------------------

    printf("%d", ans);


    return 0;
}
