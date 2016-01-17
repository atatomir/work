#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back

int tests, t, n, i, j;
int mat[20][20];

void genTest() {
    ofstream fin("input.in");

    fin << t << '\n';
    for (int aux = 1; aux <= t; aux++) {
        fin << n << '\n';

        for (i = 1; i <= n; i++)
            for (j = i + 1; j <= n; j++)
                mat[i][j] = rand() % 2, mat[j][i] = mat[i][j] ^ 1;

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++)
                fin << mat[i][j] << ' ';
            fin << '\n';
        }
    }

    fin.close();
}

bool check() {
    int how = 2 * n * t;

    system("./Good");
    system("./Brute");

    ifstream fout("output.out");
    ifstream fok("output.ok");

    for (int i = 1; i <= how; i++) {
        int a, b;

        fout >> a;
        fok >> b;

        if (a != b) {
            cerr << "Error!";
            return false;
        }
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> tests >> t >> n;

    for (;tests; tests--) {
        genTest();

        cerr << "#" << tests << ' ';
        if (!check())
            return 0;
    }


    return 0;
}
