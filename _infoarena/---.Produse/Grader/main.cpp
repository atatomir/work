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

int n, d, i;

void genTest() {
    ofstream fin("produse.in");

    int how_small = n - n / 3;
    int lim = sqrt(d);

    fin << n << ' ' << d << '\n';
    for (i = 1; i <= how_small; i++)
        fin << rand() % d + 1 << ' ';
    for (i = how_small + 1; i <= n; i++)
        fin << rand() % d + 1 << ' ';

    fin.close();
}

bool check() {
    int a, b;

    system("./Brute");
    system("./Produse");

    ifstream fout("produse.out");
    fout >> a;
    ifstream fok("produse.ok");
    fok >> b;

    if (a != b) {
        cerr << "Error";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    int tests;
    cin >> tests >> n >> d;
    for (; tests > 0; tests--) {
        genTest();

        cerr << "#" << tests << ' ';
        if (!check())
            return 0;
    }


    return 0;
}
