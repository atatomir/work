#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 355

int tests, n, i, j, k;
bool edge[maxN][maxN];
vector< pair<int, int> > wr, ver;

void genTest() {
    ofstream fin("tree2.in");
    ofstream finfo("tree2.info");

    memset(edge, 0, sizeof(edge));
    for (i = 2; i <= n; i++) {
        int fr = rand() % (i - 1) + 1;
        edge[i][fr] = edge[fr][i] = true;

        finfo << fr << ' ' << i << '\n';
    }

    wr.clear();
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            bool good = false;

            if (edge[i][j]) good = true;
            for (k = 1; k <= n; k++)
                if (edge[i][k] && edge[k][j])
                    good = true;

            if (good)
                wr.pb(mp(i, j));
        }
    }

    fin << n << ' ' << wr.size() << '\n';
    for (auto e : wr)
        fin << e.first << ' ' << e.second << '\n';

    fin.close();
}

bool check() {
    system("./Tree2");

    memset(edge, 0, sizeof(edge));

    ifstream fout("tree2.out");
    for (i = 1; i < n; i++) {
        int a, b;
        a = b = 0;
        fout >> a >> b;

        edge[a][b] = edge[b][a] = true;
    }

    ver.clear();
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            bool good = false;

            if (edge[i][j]) good = true;
            for (k = 1; k <= n; k++)
                if (edge[i][k] && edge[k][j])
                    good = true;

            if (good)
                ver.pb(mp(i, j));
        }
    }

    //!----------------------
    if (ver.size() != wr.size()) {
        cerr << "Error";
        return false;
    }

    for (int i = 0; i < wr.size(); i++)
        if (ver[i] != wr[i]) {
            cerr << "Error";
            return false;
        }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));
    cin >> tests >> n;

    for (; tests; tests--) {
        genTest();

        cerr << "#" << tests << "  ";
        if (!check())
            return 0;
    }

    return 0;
}
