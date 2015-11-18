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

#define maxN 2115
#define maxM 50011

int n_max = 2048;
int m_max = 5000;
int t_max = 1000000000;
int b_max = 10000;

int n, m, i;
vector<int> times;

void genTest() {
    n = rand() % n_max + 1;
    m = rand() % m_max + 1;

    times.clear();
    for (i = 1; i <= m; i++)
        times.pb(rand() % t_max + 1);
    sort(times.begin(), times.end());

    ofstream fin("bcrc.in");

    fin << n << ' ' << m << '\n';
    for (i = 1; i <= m; i++)
        fin << times[i - 1] << ' ' << rand() % n + 1 << ' ' << rand() % b_max + 1 << '\n';

    fin.close();
}

bool check() {
    system("./Brute");
    system("./Bcrc");

    ifstream fout("bcrc.out");
    ifstream fok("bcrc.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a == b) {
        cerr << "Passed\n";
        return true;
    }

    cerr << a << " != " << b;
    return false;

    fout.close();
    fok.close();
}

int main()
{
    srand(time(NULL));

    int tests;
    for (cin >> tests; tests > 0; tests--) {
        genTest();

        cerr << "#" << tests << ' ';
        if (!check())
            return 0;
    }

    return 0;
}
