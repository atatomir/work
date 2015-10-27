#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, i, j;
pair<int, int> P[maxN];
vector< pair<double , pair<int, int> > > work, aux;

int dad[maxN];
double ans;

int Find(int R) {
    if (dad[R] == R) return R;
    dad[R] = Find(dad[R]);
    return dad[R];
}

bool Merge(int R1, int R2) {
    R1 = Find(R1);
    R2 = Find(R2);
    if (R1 != R2) {
        dad[R2] = R1;
        return true;
    }
    return false;
}

double dist(int id1, int id2) {
    return sqrt( 1.00 * (P[id1].first - P[id2].first) * (P[id1].first - P[id2].first) +
                 1.00 * (P[id1].second - P[id2].second) * (P[id1].second - P[id2].second) );
}

int main()
{
    freopen("desen.in","r",stdin);
    freopen("desen.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second);

    for (i = 1; i <= n; i++) {
        for (j = 1; j < i; j++) work.pb(mp(dist(i, j), mp(i, j)));
        sort(work.begin(), work.end());

        aux.clear(); ans = 0;
        for (j = 1; j <= n; j++) dad[j] = j;
        for (auto e : work) {
            int R1 = e.second.first;
            int R2 = e.second.second;

            if (Merge(R1, R2)) {
                aux.pb(e);
                ans += e.first;
            }
        }

        printf("%.10lf\n", ans);
        work = aux;
    }

    return 0;
}
