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

#define maxN 277
#define each 60
#define dim 5

struct adj_list {
    int i;
    ll data[dim];

    void init() {
        for (i = 0; i < dim; i++) data[i] = 0;
    }

    bool is_in(adj_list who) {
        for (i = 0; i < 5; i++)
            if ( (data[i] & who.data[i]) != data[i] )
                return false;
        return true;
    }

    void set(int pos, int val) {
        int wh = (pos - 1) / each;
        pos -= wh * each + 1;

        int act_bit = (data[wh] >> pos) & 1;

        if (val != act_bit)
            data[wh] ^= (1LL << pos);
    }
};


int t, n, m, x, y, i;
bool adj[maxN][maxN];
adj_list work[maxN];

bool dead[maxN];

bool solve() {
    int i, j, pas;
    bool found;
    int last;

    for (pas = 1; pas < n; pas++) {
        found = false;

        for (i = 1; i <= n && !found; i++) {
            if (dead[i]) continue;
            for (j = 1; j <= n; j++) {
                if (dead[j] || i == j) continue;
                if (adj[i][j] == false) continue;

                work[j].set(i, 0);
                if (work[j].is_in(work[i])) {
                    found = true;
                    last = j;
                    break;
                }

                work[j].set(i, 1);
            }
        }

        if (!found) return false;


        work[last].init();
        dead[last] = true;
        for (i = 1; i <= n; i++) {
            adj[i][last] = adj[last][i] = false;
            work[i].set(last, 0);
        }

        //cerr << "Killed : " << last << '\n';
    }

    return true;
}

int main()
{
    freopen("tj.in","r",stdin);
    freopen("tj.out","w",stdout);

    scanf("%d", &t);

    for (; t > 0; t--) {
        memset(adj, 0, sizeof(adj));
        for (i = 1; i < maxN; i++) work[i].init();
        memset(dead, 0, sizeof(dead));

        scanf("%d%d", &n, &m);
        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            adj[x][y] = adj[y][x] = true;
            work[x].set(y, 1);
            work[y].set(x, 1);
        }

        if (solve())
            printf("DA\n");
        else
            printf("NU\n");

        //cerr << '\n';
    }


    return 0;
}
