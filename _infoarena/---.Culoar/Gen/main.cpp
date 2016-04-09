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
#define eps 0.0000001

int test, n, i;

void genTest() {
    //! generate test
    ofstream fin("culoar.in");

    fin << n << '\n';
    for (i = 1; i <= n; i++) fin << rand() % 10 + 1 << ' ' << rand() % 10 + 1 << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    double a , b;

    ifstream fout("culoar.out");
    ifstream fok("culoar.ok");

    fout >> a;
    fok >> b;

    if (-eps > a - b || a - b > eps) {
        cerr << "ERR";
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
