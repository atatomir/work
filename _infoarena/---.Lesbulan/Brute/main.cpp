#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

#define maxN 22
#define pb push_back
#define mp make_pair

int n, m, i, x, y;
vector<int> list[maxN];
bool valid[1 << maxN];
int prov[1 << maxN];
int bitUsed[1 << maxN];

void dfs(int conf) {
    if (valid[conf]) return;
    valid[conf] = true;

    for (int i = 0; i < n; i++) {
        if ( (conf & (1 << i)) == 0 ) continue;

        int go = conf ^ (1 << i);
        int to = 0;

        for (int bit = 0; bit < n; bit++) {
            if ( (go & (1 << bit)) == 0 ) continue;

            for (int j = 0; j < list[bit + 1].size(); j++) {
                int neigh = list[bit + 1][j];
                to |= 1 << (neigh - 1);
            }
        }

        if (!valid[to]) {
            prov[to] = conf;
            bitUsed[to] = i ;
        }
        dfs(to);
    }
}

void write_bin(int x) {
    for (int i = n - 1; i >= 0; i--)
        if ( (x & (1 << i)) == 0)
            cerr << '0';
        else
            cerr << '1';
}

int main()
{
    freopen("test.in", "r", stdin);

    srand(time(NULL));

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    /*cerr << n << " nodes \n\n";
    for (i = 2; i <= n; i++) {
        x = i;
        y = rand() % (i - 1) + 1;

        list[x].pb(y);
        list[y].pb(x);

        cerr << "Add edge : " << x << ' ' << y << '\n';
    }
    cerr << "\n\n";
    */

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    dfs((1 << n) - 1);
    if(valid[0]) {
        cerr << "TRUE\n";

        x = 0;
        while (prov[x] != 0) {
            write_bin(x);
            cerr << ' ' << bitUsed[x] + 1 << '\n';
            x = prov[x];
        }
    } else {
        cerr << "FALSE";
    }

    return 0;
}
