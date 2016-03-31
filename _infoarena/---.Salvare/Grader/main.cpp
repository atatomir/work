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

    ofstream fin("salvare.in");

    fin << n << '\n' << k << '\n';
    for (i = 2; i <= n; i++)
        fin << rand() % (i - 1) + 1 << ' ' << i << '\n';


    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("salvare.out");
    ifstream fok("salvare.ok");

    int a, b;

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
    cin >> test >> n >> k;


    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
