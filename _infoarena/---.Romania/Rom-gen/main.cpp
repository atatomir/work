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
    ofstream fin("romania.in");

    n = rand() % 100000 + 1;
    k = rand() % (n - 2);
    //k = n - 3;

    fin << n << ' ' << k << '\n';
    for (i = 1; i <= k; i++)
        fin << rand() % n + 1 << ' ';

    fin.close();
}

bool check() {
    //! something..
    system("./Romania");

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> test ;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
