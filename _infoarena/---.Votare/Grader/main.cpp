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

#define maxOp 500
#define maxVal 500000

int test, n, i;

void genTest() {
    //! generate test

    ofstream fin("votare.in");

    n = rand() % maxOp + 1;

    fin << n << '\n';
    for (i = 1; i <= n; i++)
        if (rand() % 2 == 0)
            fin << '0' << ' ' << rand() % maxVal << ' ' << rand() % maxVal << '\n';
        else
            fin << '2' << ' ' << rand() % maxVal << ' ' << rand() % maxVal << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("votare.out");
    ifstream fok("votare.ok");

    int i, a, b;

    a = b = 0;
    for (i = 1; i <= n; i++) {
        fout >> a;
        fok >> b;

        if (a != b) {
            cerr << "Error!";
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
    cin >> test;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
