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

int test, n, i;

void genTest() {
    ofstream fin("magnet.in");

    fin << 2 << '\n';

    fin << n << '\n';

    for (i = 1; i <= n; i++) fin << rand() % 5 << ' ';
    fin << '\n';

    for (i = 1; i <= n; i++) fin << rand() % 5 << ' ';
    fin << '\n';

    //!-------------------
    n--;


    fin << n << '\n';

    for (i = 1; i <= n; i++) fin << rand() % 100 << ' ';
    fin << '\n';

    for (i = 1; i <= n; i++) fin << rand() % 100 << ' ';
    fin << '\n';

    n++;

    fin.close();
}

bool check() {
    //! something..
    if(system("./good") != 0) exit(0);


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
