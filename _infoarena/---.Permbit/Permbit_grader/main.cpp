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

const int maxN = 21;
const int maxM = 9;

int test;
int tp, n, m, i, j;
char data[maxN + 11][maxM + 11];
int p[maxM + 11];

void genTest() {
    ofstream fin("permbit.in");

    tp = (rand() % 3) + 1;
    n = (rand() % maxN) + 1;
    m = (rand() % maxM) + 1;

    cerr << tp << ' ';

    memset(data, 0, sizeof(data));
    for (i = 1; i <= m; i++) {
        p[i] = i;
        data[1][i] = '0' + (rand() % 2);
    }
    random_shuffle(p + 1, p + m + 1);

    for (i = 1; i < n; i++) {
        for (j = 1; j <= m; j++) {
            data[i + 1][p[j]] = data[i][j];
        }
    }

    fin << tp << ' ' << n << ' ' << m << '\n';
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) fin << data[i][j];
        fin << '\n';
    }

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("permbit.out");
    ifstream fok("permbit.ok");

    int a, b;
    for (i = 1; i <= m; i++) {
        fout >> a;
        fok >> b;

        if (a != b) {
            cerr << "Error\n";
            return false;
        }

        if (tp == 3) break;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> test;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
