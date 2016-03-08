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

#define maxOp 5
#define maxVal 4000

int test, n, i;

void genTest() {
    //! generate test
    ofstream fin("photoshop.in");

    n = rand() % maxOp + 1;

    fin << n << '\n';

    for (i = 1; i <= n; i++) {
        if (rand() % 3 == 0) {
            fin << 0 << ' ' << rand() % maxVal << ' ' << rand() % maxVal << '\n';
        } else {
            int a, b, c, d;
            a = rand() % maxVal;
            b = rand() % maxVal;
            c = rand() % maxVal;
            d = rand() % maxVal;

            if (a > c) swap(a, c);
            if (b < d) swap(b, d);

            fin << '2' << ' ' << a << ' ' << b << ' ' << c << ' ' << d << '\n';
        }
    }

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("photoshop.out");
    ifstream fok("photoshop.ok");

    int a, b;

    for (int verif = 0; verif <= maxOp; verif++) {
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
