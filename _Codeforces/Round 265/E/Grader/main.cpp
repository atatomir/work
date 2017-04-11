#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int tests;
int n, m, i, x, y, z, S, T;
map< pair<int, int>, bool> M;

void genTest() {
    ofstream fin("test.in");
    fin << n << ' ' << m << '\n';

    M.clear();
    for (i = 1; i <= m; i++) {
        do {
            x = 1 + (rand() % n);
            y = 1 + (rand() % n);
        } while (M[mp(x, y)] == true || x == y);
        M[mp(x, y)] = true;
        M[mp(y, x)] = true;
        z = rand() % 30;

        fin << x << ' ' << y << ' ' << z << '\n';
    }

    S = 1 + (rand() % n);
    T = 1 + (rand() % n);
    fin << S << ' ' << T;

    fin.close();
}

bool check() {
    system("./good");
    system("./brute");

    ifstream fout("test.out");
    ifstream fok("test.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Error!\n";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> tests >> n >> m;
    while (tests--) {
        cerr << "#" << tests << ':';

        genTest();
        if (!check())
            return 0;
    }


    return 0;
}
