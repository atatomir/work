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

const int n = 100000;
const int m = 10000;
const int vmax = 100000;

int test, i, l, r, cnt, tp, v1, v2;

void genTest() {
    ofstream fin("test.in");

    cnt = 0;
    fin << n << ' ' << m << '\n';
    for (i = 1; i <= n; i++) fin << (rand() % vmax) + 1 << ' ';
    fin << '\n';
    for (i = 1; i <= m; i++) {
        l = (rand() % n) + 1;
        r = (rand() % n) + 1;
        tp = (rand() % 2) + 1;
        if (tp == 2) cnt++;

        if (l > r) swap(l, r);
        fin << tp << ' ' << l << ' ' << r << ' ' << (rand() % vmax) + 1 << '\n';
    }

    fin.close();
}

bool check() {
    //! something..
    system("./Brute");
    system("./good");

    ifstream fout("test.out");
    ifstream fok("test.ok");

    for (i = 1; i <= cnt; i++) {
        fout >> v1;
        fok >> v2;
        if (v1 != v2) {
            cerr << "Error\n";
            return false;
        }
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
