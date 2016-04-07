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

int test;
int n, k, i;
int maxi = 10;

void genTest() {
    //! generate test
    ofstream fout("cbarn.in");

    fout << n << ' ' << k << '\n';
    for (i = 1; i <= n; i++) fout << rand() % maxi + 1 << '\n';

    fout.clear();
}

bool check() {
    //! something..
    system("./Brute");
    system("./CBarn");

    ifstream fin("cbarn.out");
    ifstream fok("cbarn.ok");

    int a, b;
    fin >> a;
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
