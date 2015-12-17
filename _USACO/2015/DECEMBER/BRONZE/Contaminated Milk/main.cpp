#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 57
#define maxM 57

int n, m, d, s, i;
int pers, bott, when;
vector< pair<int, int> > drink[maxN];

int probably[maxM];
int how_many[maxM];

bool pers_drink[maxN][maxM];
bool pers_drink_sick[maxN][maxM];
int ans;

int main()
{
    freopen("badmilk.in","r",stdin);
    freopen("badmilk.out","w",stdout);


    scanf("%d%d%d%d", &n, &m, &d, &s);
    for (i = 1; i <= d; i++) {
        scanf("%d%d%d", &pers, &bott, &when);
        drink[pers].pb(mp(when, bott));

        if (pers_drink[pers][bott] == false)
            how_many[bott]++;
        pers_drink[pers][bott] = true;
    }

    for (i = 1; i <= s; i++) {
        scanf("%d%d", &pers, &when);

        for (auto e : drink[pers]) {
            if (e.first >= when) continue;

            if (pers_drink_sick[pers][e.second] == false)
                probably[e.second]++;
            pers_drink_sick[pers][e.second] = true;
        }
    }

    for (i = 1; i <= m; i++) {
        if (probably[i] != s) continue;
        ans = max(ans, how_many[i]);
    }

    printf("%d", ans);


    return 0;
}
