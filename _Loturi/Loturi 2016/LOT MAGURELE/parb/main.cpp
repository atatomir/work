#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 100011
#define maxLog 20

struct triple {
    int a, b, id;

    bool operator<(const triple& who)const {
        return mp(a, b) < mp(who.a, who.b);
    }

    bool operator==(const triple& who) {
        return mp(a, b) == mp(who.a, who.b);
    }
};

int n, q, i, x, y, llog;
char c;
vector< pair<int, char> > list[maxN];

bool us[maxN];
int lvl[maxN];
int dad[maxLog][maxN];
int sa[maxLog][maxN]; //! suffix array pe copacel

vector<triple> aux;
int order[maxN];
int where[maxN];



void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to.first]) continue;
        lvl[to.first] = lvl[node] + 1;
        dad[0][to.first] = node;
        sa[0][to.first] = to.second - 'a';
        dfs(to.first);
    }
}

void compute_dad() {
    int i, j;

    for(llog = 0; (1 << llog) <= n; llog++);
    llog++;

    for (i = 1; i < llog; i++)
        for (j = 1; j <= n; j++)
            dad[i][j] = dad[i - 1][ dad[i - 1][j] ];
}

void compute_sa() {
    int i, j;

    for (i = 1; i < llog; i++) {
        aux.clear();
        for (j = 1; j <= n; j++) {
            if (dad[i - 1][j] == 0)
                aux.pb({sa[i - 1][j], -1, j});
            else
                aux.pb({sa[i - 1][j], sa[i - 1][ dad[i - 1][j] ], j});
        }

        sort(aux.begin(), aux.end());
        sa[i][ aux[0].id ] = 0;
        for (j = 1; j < (int)aux.size(); j++) {
            if (aux[j - 1] == aux[j])
                sa[i][ aux[j].id ] = sa[i][ aux[j - 1].id ];
            else
                sa[i][ aux[j].id ] = j;
        }

        if (i + 1 == llog) {
            for (j = 0; j < n; j++) {
                order[j + 1] = aux[j].id;
                where[ aux[j].id ] = j + 1;
            }
        }
    }
}

int lcp(int n1, int n2) {
    int ans = 0;

    for (int step = llog - 1; step >= 0 && n1 != 1 && n2 != 1; step--)
        if (dad[step][n1] != 0 && dad[step][n2] != 0)
            if (sa[step][n1] == sa[step][n2])
                n1 = dad[step][n1], n2 = dad[step][n2], ans += (1 << step);

    return ans;
}

int src_left(int pos, int need) {
    int ans = 0;

    for (int step = (1 << llog); step > 0; step >>= 1)
        if (ans + step < pos)
            if (lcp(order[ans + step], order[pos]) < need)
                ans += step;

    return ans + 1;
}

int src_right(int pos, int need) {
    int ans = pos;

    for (int step = (1 << llog); step > 0; step >>= 1)
        if (ans + step <= n)
            if (lcp(order[ans + step], order[pos]) >= need)
                ans += step;

    return ans;
}


int main()
{
    freopen("parb.in", "r", stdin);
    freopen("parb.out", "w", stdout);

    scanf("%d%d", &n, &q);
    for (i = 1; i < n; i++) {
        scanf("%d%d %c\n", &x, &y, &c);
        list[x].pb(mp(y, c));
        list[y].pb(mp(x, c));
    }

    dfs(1); sa[0][1] = - 1;
    compute_dad();
    compute_sa();

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &x, &y);

        int need = lvl[y] - lvl[x];
        int l = src_left(where[y], need);
        int r = src_right(where[y], need);

        printf("%d\n", r - l + 1);
    }



    return 0;
}
