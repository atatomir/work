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

#define maxi 10

int test;
int n, m, i;

void genTest() {
    ofstream fin("3max.in");

    fin << n << ' ' << m << '\n';
    for (i = 1; i <= n; i++) fin << rand() % (2 * maxi) - maxi << ' ';
    fin << '\n';

    for (i = 1; i <= m; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;

        if (a > b) swap(a, b);
        fin << a << ' ' << b << '\n';
    }

    fin.close();
}

bool check() {
    //! something..
    system("./Brute");
    system("./3max");

    ll a, b;
    ifstream fout("3max.out");
    ifstream fok("3max.ok");

    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Error!";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    //! read t, n, ....
    cin >> test >> n >> m;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
