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

int test, n;

void genTest() {
    //! generate test
    ofstream fin("landscape.in");

    fin << n << ' ' << rand() % 100 << ' ' << rand() % 100 << ' ' << rand() % 100 << '\n';
    for (int i = 1; i <= n; i++)
        fin << rand() % 11 << ' ' << rand() % 11 << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("landscape.out");
    ifstream fok("landscape.ok");

    ll a, b;
    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Err";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    //! read t, n, ....
    cin >> test >> n;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
