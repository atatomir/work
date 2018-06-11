#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 11;

int tests, i, j;
char s[maxN];

void run_with_time(string s) {
    float t1 = clock();
    system(s.c_str());
    float t2 = clock();

    //cerr << ((1.00 * t2 - 1.00 * t1) / (1.00 * CLOCKS_PER_SEC)) << "s ";
}

void genTest() {
    int n, m, i, j;
    vector< pair<int, int> > aux = {};

    n = (rand() % maxN) + 1;

    ofstream fin("smooth2.in");

    for (i = 1; i <= n; i++) fin << (char)('a' + (rand() % 3));

    fin.close();
}

bool check() {
    run_with_time("./good");
    run_with_time("./brute");

    ifstream fout("smooth2.out");
    ifstream fok("smooth2.ok");

    int a, b;
    fout >> a;
    fok >> b;
    cerr << a << ' ' << b << ' ';

    if (a != b) {
        cerr << "Err\n";
        return false;
    }

    cerr << "Ok\n";
    return true;
}

int main()
{
    srand(time(NULL));
    cin >> tests;
    while(tests--) {
        cerr << tests << ": ";
        genTest();
        if (!check()) return 0;
    }


    return 0;
}
