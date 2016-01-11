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

int n, m, i, x, y, k, j;
bool edge[maxN][maxN];
bool ans_edge[maxN][maxN];
bool fix[maxN];

bool rez[maxN][maxN];
bool ver[maxN][maxN];

bool incl[maxN][maxN];

int R;
vector<int> aux;
int maybe_leaf[maxN];

void solve(int node) {
    int i, j, k;

    //! remove fixed nodes
    for (i = 1; i <= n; i++)
        if ( fix[i] )
            edge[node][i] = edge[i][node] = false;

    for (i = 1; i <= n; i++) {
        if (ans_edge[node][i] == false)
            continue;

        //! remove fixed nodes
        for (j = 1; j <= n; j++)
            if ( fix[j] )
                edge[i][j] = edge[j][i] = false;

        //! let's solve the subtree of i
        aux.clear();
        for (j = 1; j <= n; j++)
            if (edge[node][j] == true && edge[i][j] == true)
                aux.pb(j);

        //! add new edges and nodes
        for (auto e : aux) {
            ans_edge[i][e] = true;
            fix[e] = true;
        }
    }

    //! solve sons of node
    for (i = 1; i <= n; i++)
        if (ans_edge[node][i])
            solve(i);
}

void little_star() {
    for (int i = 2; i <= n; i++)
        printf("%d %d\n", 1, i);
};

bool check() {
    int i, j, k;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            ans_edge[i][j] |= ans_edge[j][i], ans_edge[j][i] |= ans_edge[i][j];

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (i == j) continue;

            bool found = false;

            if (ans_edge[i][j])
                found = true;

            for (k = 1; k <= n; k++) {
                if (k == i || k == j) continue;

                if (ans_edge[i][k] && ans_edge[k][j])
                    found = true;
            }

            if (found)
                ver[i][j] = ver[j][i] = true;
            else
                ver[i][j] = ver[j][i] = false;
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (ver[i][j] != rez[i][j])
                return false;

    return true;
}

void find_root() {
    int i, j, k;

    for (i = 1; i <= n; i++) {
        //! try with j
        for (j = 1; j <= n; j++) {
            if (i == j)
                continue;

            bool good = true;
            for (k = 1; k <= n; k++)
                if (k != i && k != j)
                    if (edge[i][k] == true && edge[j][k] == false)
                        good = false;


            if (good) {
                maybe_leaf[i]++;
                incl[i][j] = true;
            }
        }
    }

    R = 1;
    for (i = 2; i <= n; i++)
        if (maybe_leaf[i] > maybe_leaf[R])
            R = i;

    vector<int> possible;
    possible.clear();

    for (i = 1; i <= n; i++)
        if (incl[R][i] )
            possible.pb(i);

    random_shuffle(possible.begin(), possible.end());
    memcpy(rez, edge, sizeof(rez));

    for (auto dad : possible) {
        //! test every root

        memcpy(edge, rez, sizeof(rez));
        memset(fix, 0, sizeof(fix));
        memset(ans_edge, 0, sizeof(ans_edge));

        ans_edge[R][dad] = true;
        fix[R] = fix[dad] = true;

        solve(R);

        if (check())
            return;
    }

    cerr << "Root not found";

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

    if (m == (n * (n - 1)) / 2 ) {
        little_star();
        return 0;
    }

    find_root();

    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            if (ans_edge[i][j])
                printf("%d %d\n", i, j);



    return 0;
}
