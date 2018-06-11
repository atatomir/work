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

const int maxN = 1000;
const int maxM = 1000;

int tests, i, j;

void run_with_time(string s) {
    float t1 = clock();
    system(s.c_str());
    float t2 = clock();

    cerr << ((1.00 * t2 - 1.00 * t1) / (1.00 * CLOCKS_PER_SEC)) << "s ";
}

void genTest() {
    int n, m, i, j;
    vector<int> aux;

    n = (rand() % maxN) + 1;
    m = (rand() % maxM) + 1;

    aux.clear();
    for (i = 1; i <= n * m; i++) aux.pb(i);
    random_shuffle(aux.begin(), aux.end());

    ofstream fin("zoro.in");

    fin << n << ' ' << m << '\n';
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            fin << aux.back() << ' ';
            aux.pop_back();
        }
        fin << '\n';
    }

    fin.close();
}

bool check() {
    run_with_time("./good");
    run_with_time("./brute");

    ifstream fout("zoro.out");
    ifstream fok("zoro.ok");

    int a, b;
    fout >> a;
    fok >> b;
    if (a != b) {
        cerr << "Err\n";
        return false;
    }

    cerr << "Ok\n";
    return true;
}

int main()
{

    cin >> tests;
    while(tests--) {
        cerr << tests << ": ";
        genTest();
        if (!check()) return 0;
    }


    return 0;
}
