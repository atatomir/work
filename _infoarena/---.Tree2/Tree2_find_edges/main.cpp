#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 355

int n, i, j, x, y, m;
bool edge[maxN][maxN];
bool ans_edge[maxN][maxN];
vector<int> aux;
vector<int> brother;
bool fix[maxN];
int cnt[maxN];

void little_star() {
    for (int i = 1; i < n; i++)
        printf("%d %d\n", i, n);

    exit(0);
}

void solve() {
    //! solve internal edges
    int i, j, k;

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            aux.clear();

            for (k = 1; k <= n; k++)
                if (edge[i][k] && edge[j][k])
                    aux.pb(k);

            if (aux.size() != 2) continue;
            if (edge[i][j]) continue;

            ans_edge[ aux[0] ][ aux[1] ] = true;
            ans_edge[ aux[1] ][ aux[0] ] = true;

            fix[aux[0]] = true;
            fix[aux[1]] = true;
        }
    }
}

void add_leaves() {
    int i, j;

    for (i = 1; i <= n; i++) {
        if (fix[i]) continue;

        //! get neighbours
        aux.clear();
        brother.clear();

        for (j = 1; j <= n; j++)
            if (edge[i][j])
                if (fix[j])
                    aux.pb(j);
                else
                    brother.pb(j);

            memset(cnt, 0, sizeof(cnt));
            for (auto e1 : aux)
                for (auto e2 : aux)
                    if (ans_edge[e1][e2])
                        cnt[e1]++, cnt[e2]++;

        if (aux.size() != 2) {
            int daddy = aux[0];
            for (auto e : aux)
                if (cnt[e] > cnt[daddy])
                    daddy = e;

            //! add leaves
            brother.pb(i);
            for (auto e : brother) {
                fix[e] = true;
                ans_edge[daddy][e] = ans_edge[e][daddy] = true;
            }

            continue;
        }

        //! just two nodes

        int id = aux[0];
        bool good_first = true;
        for (j = 1; j <= n; j++)
            if (j != i && j != id && fix[j] == true)
                if (ans_edge[id][j] == true && edge[j][i] == false)
                    good_first = false;

        if (!good_first)
            swap(aux[0], aux[1]);

        fix[i] = true;
        ans_edge[i][ aux[0] ] = ans_edge[ aux[0] ][i] = true;
    }
}

int main()
{
    freopen("tree2.in","r",stdin);
    freopen("tree2.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        edge[x][y] = edge[y][x] = true;
    }

    if (m == (n * (n - 1)) / 2)
        little_star();

    solve();
    add_leaves();

    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            if (ans_edge[i][j])
                printf("%d %d\n", i, j);


    return 0;
}
