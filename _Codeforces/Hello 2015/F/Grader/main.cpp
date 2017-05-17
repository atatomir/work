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
#define ll long long

int tests, n, i, m;

void genTest() {
    ofstream fin("test.in");

    fin << n << ' ' << m << '\n';
    for (i = 2; i <= n; i++) {
        fin << i << ' ' << 1 + (rand() % (i - 1)) << ' ' << 1 + (rand() % 1000000000) << '\n';
    }

    for (i = 1; i <= m; i++) {
        fin << 1 + (rand() % n) << ' ' << rand() % 100000000000000LL << '\n';
    }

    fin.close();
}

bool check() {
    system("./good");
    system("./brute");

    ifstream fout("test.out");
    ifstream fok("test.ok");

    int i, a, b;
    for (i = 1; i <= m; i++) {
        fout >> a;
        fok >> b;

        if (a != b) {
            cerr << "Error!\n";
            return false;
        }
    }

    cerr << "Passed\n";
    return true;
}

int main()
{

    cin >> tests >> n >> m;
    while (tests--) {
        cerr << "#" << tests << " : ";

        genTest();
        if (!check())
            return 0;
    }



    return 0;
}
