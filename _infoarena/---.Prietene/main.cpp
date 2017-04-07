#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 155

int t, ti;
int n, m, i, x, y, q;
bool adj[maxN][maxN];
int sup[maxN][maxN];
bitset<maxN> data[maxN];
char op;

bool r1, r2, r3, r4;

void add(int x, int y) {
    static int node;

    adj[x][y] = true;
    if (++sup[x][y] == 1) data[x][y] = true;

    for (node = 1; node <= n; node++) {
        if (adj[node][x])
            if (++sup[node][y] == 1) data[node][y] = true;
        if (adj[y][node])
            if (++sup[x][node] == 1) data[x][node] = true;
    }
}

void rm(int x, int y) {
    static int node;

    adj[x][y] = false;
    if (--sup[x][y] == 0) data[x][y] = false;

    for (node = 1; node <= n; node++) {
        if (adj[node][x])
            if (--sup[node][y] == 0) data[node][y] = false;
        if (adj[y][node])
            if (--sup[x][node] == 0) data[x][node] = false;
    }
}

int main()
{
    freopen("prietene.in","r",stdin);
    freopen("prietene.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);

        memset(adj, 0, sizeof(adj));
        memset(sup, 0, sizeof(sup));
        for (i = 1; i <= n; i++) data[i].reset();

        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            add(x, y);
        }

        scanf("%d\n", &q);
        for (i = 1; i <= q; i++) {
            scanf("%c%d%d\n", &op, &x, &y);

            if (op == 'a') {
                add(x, y);
            }

            if (op == 'd') {
                rm(x, y);
            }

            if (op == 'q') {
                r1 = data[x][x]; data[x][x] = 0;
                r2 = data[x][y]; data[x][y] = 0;
                r3 = data[y][y]; data[y][y] = 0;
                r4 = data[y][x]; data[y][x] = 0;

                if (data[x] == data[y])
                    printf("YES\n");
                else
                    printf("NO\n");

                data[x][x] = r1;
                data[x][y] = r2;
                data[y][y] = r3;
                data[y][x] = r4;
            }
        }
    }


    return 0;
}
