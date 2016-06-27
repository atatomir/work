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

int test, n, k, i;

void genTest() {
    //! generate test
    ofstream fin("oneouts.in");

    fin << n << ' ' << k << '\n';

    for (i = 1; i <= n; i++) fin << 1 + rand() % 10 << ' ';
    fin << '\n';

    for (i = 1; i <= n; i++) fin << 1 + rand() % 10 << ' ';
    fin << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("oneouts.out");
    ifstream fok("oneouts.ok");

    int a, b;

    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Err\n";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    //! read t, n, ....
    cin >> n >> k;

    test = 100;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
