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
    //! generate test
    ofstream fin("262144.in");

    fin << n << '\n';
    for (i = 1; i <= n; i++) fin << rand() % 3 + 1 << ' ';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("262144.out");
    ifstream fok("262144.ok");

    int a, b;
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
