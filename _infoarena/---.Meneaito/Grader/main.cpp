#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back

int n_max = 5;
int n, i, a, b;

vector< pair<int, int> > v;

void genTest() {
    ofstream fin("meneaito.in");

    n = rand() % n_max + 1;
    if (n < 3) n = 11;
    fin << n << '\n';

    v.clear();
    for (i = 2; i < n; i++) {
        a = rand() % n + 1;
        b = rand() % n + 1;
        if (a > b) swap(a, b);

        v.pb(mp(a, b));
    }

    for (auto who : v)
        fin << who.first << ' ';
    fin << '\n';

    for (auto who : v)
        fin << who.second << ' ';
    fin << '\n';

    fin.close();
}

bool check() {
    system("./Brute");
    system("./Meneaito");

    ifstream fout("meneaito.out");
    ifstream fok("meneaito.ok");

    fout >> a;
    fok >> b;

    if (a == b) {
        cerr << "Passed\n";
        return true;
    }

    cerr << a << " != " << b;
    return false;
}

int main()
{
    int tests;

    for (cin >> tests; tests > 0; tests--) {
        genTest();

        cerr << "#" << tests << " ";

        if (!check())
            return 0;
    }

    return 0;
}
