#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10011
#define maxR 100000
#define maxVal 100000000

int n, m, i, j, x, y, r;
int xx[maxN];
int yy[maxN];
int rr[maxN];

bool common(int xx1, int yy1, int r1, int xx2, int yy2, int r2) {
    return 1LL * (xx2 - xx1) * (xx2 - xx1) +  1LL * (yy2 - yy1) * (yy2 - yy1) <= 1LL * (r1 + r2) * (r1 + r2);
}

void genTest() {
    ofstream fout("nuke.in");

    n = rand() % (2 * maxN) + 1;
    m = rand() % maxN + 1;
    fout << n << ' ' << m << '\n';

    for (i = 1; i <= n; i++) {
        x = rand() % (2 * maxVal) + maxVal;
        y = rand() % (2 * maxVal) + maxVal;

        fout << x << ' ' << y << '\n';
    }

    for (i = 1; i <= m; i++) {
        x = rand() % (2 * maxVal) + maxVal;
        y = rand() % (2 * maxVal) + maxVal;
        r = rand() % maxR + 1;


        bool good = true;
        for (j = 1; j < i; j++) {
            if (common(x, y, r, xx[j], yy[j], rr[j])) {
                good = false;
                break;
            }
        }

        if (good == false) {
            i--;
            continue;
        }

        fout << x << ' ' << y << ' ' << r << '\n';
        xx[i] = x;
        yy[i] = y;
        rr[i] = r;
    }

    fout.close();
}

bool check() {
    system("./nuke");
    system("./brute");


    ifstream fin("nuke.in");
    ifstream fout("nuke.out");
    ifstream fok("nuke.ok");

    fin >> n >> m;
    for (i = 1; i <= m; i++) {
        fout >> x;
        fok >> y;
        if (x != y) {
            cerr << "Error " << x << "  " << y;
            return false;
        }
    }

    cerr << "Passed\n";
    return true;
}


int main()
{
    srand(time(NULL));

    int tests = 10;
    while (tests--) {
        cerr << "#" << tests << ' ';
        genTest();
        if (!check())
            return 0;
    }


    return 0;
}
