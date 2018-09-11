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
int n = 100;
int max_cost = 100000;

void genTest() {
    ofstream fin("craciun.in");
    int i;

    fin << n << '\n';
    for (i = 1; i <= n; i++) fin << (rand() % max_cost) << ' ';
    fin << '\n';
    //for (i = 2; i <= n; i++) fin << i / 2 << ' ';
    for (i = 2; i <= n; i++) fin << ((rand() % (i - 1)) + 1) << ' ';

    fin.close();
}

bool check() {
    //! something..
    system("./Brute");
    system("./Craciun");

    double a, b, dif;
    ifstream fout("craciun.out");
    ifstream fok("craciun.ok");

    fout >> a;
    fok >> b;
    dif = abs(a - b);
    if (dif > 1e-4) {
        cerr << "Err\n";
        return false;
    }


    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> test;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
