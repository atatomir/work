#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 30

int n, m, i, j;
int l[maxN], r[maxN]; //! cuplaj
bool sup_l[maxN], sup_r[maxN]; //! support
char s[maxN];
vector<int> list[maxN];

bool us[maxN];

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (auto to : list[node]) {
        if (r[to] == 0) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    for (auto to : list[node]) {
        if (pairUp(r[to])) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    return false;
}

void support(int node) {
    for (auto to : list[node]) {
        if (sup_r[to] == true) continue;

        sup_r[to] = true;
        sup_l[r[to]] = false;
        support(r[to]);
    }
}

int main()
{
    freopen("paznici.in","r",stdin);
    freopen("paznici.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s+ 1);
        for (j = 1; j <= m; j++) {
            if (s[j] == '0') continue;

            list[i].pb(j);
        }
    }

    bool need = true;
    while (need) {
        need = false;
        memset(us, 0, sizeof(us));

        for (i = 1; i <= n; i++)
            if (l[i] == 0)
                need |= pairUp(i);
    }

    for (i = 1; i <= n; i++)
        if (l[i] != 0)
            sup_l[i] = true;

    for (i = 1; i <= n; i++)
        if (sup_l[i] == false)
            support(i);

    for (i = 1; i <= n; i++)
        if (sup_l[i]) printf("%c", 'A' + i - 1);

    for (i = 1; i <= n; i++)
        if (sup_r[i]) printf("%c", 'a' + i - 1);


    return 0;
}
