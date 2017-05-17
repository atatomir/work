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

void genTest() {
    //! generate testŝ

    ofstream fin("test.in");

    int n = rand() % 10000; n++;
    int m = rand() % 300000; m++;

    fin << n << ' ' << m << '\n';
    for (int i = 1; i <= n; i++)
        fin << 1 + (rand() % 3) << ' ' << 1 + (rand() % 1000000000) << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("test.out");
    ifstream fok("test.ok");

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
    cin >> test;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
