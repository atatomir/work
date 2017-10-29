#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 900;
const int maxK = 12;
const int maxQ = 900;
const int maxVal = 1000000000;

int tests, n, k, q, i, j, tp, x, y, qq, cnt, tp3;

void gen_test() {
    n = 1 + (rand() % maxN);
    k = 1 + (rand() % maxK);
    q = 1 + (rand() % maxQ);

    ofstream fin("test.in");

    fin << n << ' ' << k << ' ' << q << '\n';
    for (i = 1; i <= k; i++, fin << '\n')
        for (j = 1; j <= n; j++)
            fin << rand() % maxVal << ' ';

    cnt = k; tp3 = 0;
    for (qq = 1; qq <= q; qq++) {
        tp = 1 + (rand() % 3);

        if (tp <= 2) {
            x = 1 + (rand() % cnt);
            y = 1 + (rand() % cnt);
            cnt++;
        } else {
            x = 1 + (rand() % cnt);
            y = 1 + (rand() % n);
            tp3++;
        }

        fin << tp << ' ' << x << ' ' << y << '\n';
    }

    fin.close();
}

bool check() {
    system("./brute");
    system("./good");
    ifstream fout("test.out");
    ifstream fok("test.ok");

    for (int i = 1; i <= tp3; i++) {
        x = -1; y = -2;
        fout >> x;
        fok >> y;
        if (x != y) {
            cout << "Error\n";
            return false;
        }
    }

    return true;
}

int main()
{
    srand(time(NULL));

    cin >> tests;
    while (tests--) {
        gen_test();
        cout << tests << ' ';
        if (!check())
            return false;
        cout << "OK\n";
    }



    return 0;
}
