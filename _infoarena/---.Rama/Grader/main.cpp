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

int n, m, i, j, tests;

void genTest() {
    ofstream fin("rama.in");

    fin << n << ' ' << m << '\n';
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++)
            fin << (char)('0' + (rand() % 2));
        fin << '\n';
    }

    fin.close();
}

bool check() {
    system("./Brute");
    system("./Rama");

    ifstream fout("rama.out");
    ifstream fok("rama.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << a << " != " << b << '\n';
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    n = m = 100;
    cin >> tests >> n >> m;
    for (; tests > 0; tests--) {
        genTest();

        cerr << "#" << tests << ' ';
        if (!check())
            return 0;
    }



    return 0;
}
