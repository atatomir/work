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

const int maxN = 10;
const int maxQ = 20;

int test;
int n, q, i, x, y;

void genTest() {
    ofstream fin("test.in");

    n = 1 + (rand() % maxN);
    q = maxQ;
    fin << n << ' ' << q << '\n';
    for (i = 2; i <= n; i++) fin << 1 + (rand() % (i - 1)) << ' ';
    fin << '\n';
    for (i = 1; i <= q; i++) fin << 1 + (rand() % 3) << ' ' << 1 + (rand() % n) << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("test.out");
    ifstream fok("test.ok");
    string a, b;

    while (fout >> a) {
        fok >> b;
        if (a != b) {
            cerr << "Err\n";
            return false;
        }
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
