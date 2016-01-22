#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 256

int tests;
int n, i, k, j, m;
bool adj[maxN][maxN];

void genDef() {
    int i;

    ofstream fin("dep.in");

    fin << n << ' ' << n - 1 << ' ' << k << '\n';
    for (i = 2; i <= n; i++)
        fin << i << ' ' << i / 2 << '\n';

    fin.close();
}

void genTest() {
    int i, j;
    int v1, v2;

    memset(adj, 0, sizeof(adj));
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;

            if (rand() % 350 == 0)
                adj[i][j] = true;
        }
    }

    bool change = true;
    while (change) {
        change = false;

        for (i = 1; i <= n; i++) {
            for (v1 = 1; v1 <= n; v1++) {
                if (adj[i][v1] == false) continue;

                for (v2 = v1 + 1; v2 <= n; v2++) {
                    if (adj[i][v2] == false) continue;

                    if (adj[v1][v2] || adj[v2][v1]) continue;
                    if (rand() % 2)
                        adj[v1][v2] = true;
                    else
                        adj[v2][v1] = true;
                    change = true;
                }
            }
        }
    }

    m = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            m += adj[i][j];

    ofstream fin("dep.in");

    fin << n << ' ' << m << ' ' << k << '\n';
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (adj[i][j])
                fin << i << ' ' << j << '\n';

    fin.close();
}

void print_test() {
    ofstream fin("dep.in");

    fin << n << ' ' << m << ' ' << k << '\n';
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (adj[i][j])
                fin << i << ' ' << j << '\n';

    fin.close();
}

bool check() {
    system("./Brute");
    system("./Dep");

    ifstream fout("dep.out");
    ifstream fok("dep.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a != 0) cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!";

    if (a == b) {
        cerr << "Passed\n";
        return true;
    } else {
        cerr << "Error\n";
        return true;
    }
}

int main()
{
    srand(time(NULL));

    cin >> tests >> n >> k;


    for(; tests; tests--) {
        genTest();

        cerr << "#" << tests << " ";

        if (!check())
            return 0;
    }


    return 0;
}
