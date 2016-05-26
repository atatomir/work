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

int test;

int T, A, B, i;

void genTest() {
    //! generate test

    ofstream fin("taxi.in");

    fin << T << '\n';
    for (i = 1; i <= T; i++) {
        fin << A << ' ' << B << ' ';
        fin << rand() % (A + 1) << ' ' << rand() % (B + 1) << ' ';
        fin << rand() % (A + 1) << ' ' << rand() % (B + 1) << '\n';
    }


    fin.close();
}

bool check() {
    system("./brute");
    system("./good");

    ifstream fout("taxi.out");
    ifstream fok("taxi.ok");

    ll a, b;
    for (i = 1; i <= T; i++) {
        fout >> a;
        fok >> b;

        if (a != b) {
            cerr << "err";
            return false;
        }
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    //! read t, n, ....

    cin >> test >> T >> A >> B;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
