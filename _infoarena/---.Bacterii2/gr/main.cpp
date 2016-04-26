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

int test, n, m, i;

void genTest() {
    //! generate test

    ofstream fin("bacterii2.in");

    fin << "1\n";

    fin << n << '\n';
    for (i = 1; i <= n; i++) fin << rand() % 30000 + 1 << ' ';
    fin << '\n';

    fin << m << '\n';
    for (i = 1; i <= m; i++) fin << rand() % 30000 + 1 << ' ';
    fin << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("bacterii2.out");
    ifstream fok("bacterii2.ok");

    int a, b, c, d;
    for (int pas = 1; pas <= 60000; pas++) {
        fout >> a >> b ;
        fok >> c >> d;

        if (a != c || b != d) {
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
