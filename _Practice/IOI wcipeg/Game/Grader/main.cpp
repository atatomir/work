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

#define maxOp 250000
#define maxVal 1000000000

#define x1 xx1
#define y1 yy1
#define x2 xx2
#define y2 yy2

int test, n, i, dx, dy;
int queries, x1, y1, x2, y2;


void genTest() {
    //! generate test
    ofstream fin("test.in");
    queries = 0;

    dx = rand() % maxVal + 1;
    dy = rand() % maxVal + 1;
    n = rand() % maxOp + 1;

    fin << dx << ' ' << dy << ' ' << n << '\n';
    for (i = 1; i <= n; i++) {
        if (rand() % 2 == 0) {
            fin << "1 " << rand() % dx << ' ' << rand() % dy << ' ' << rand() % maxVal << '\n';
        } else {
            queries++;
            x1 = rand() % dx;
            x2 = rand() % dx;
            y1 = rand() % dy;
            y2 = rand() % dy;

            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);

            fin << "2 " << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
        }
    }

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("test.out");
    ifstream fok("test.ok");

    int a, b;

    for (i = 1; i <= queries; i++) {
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
