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

const int maxN = 23;
const int maxM = 23;

int tests, i, j;
char mat[maxN][maxN];

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
    m = (rand() % maxM) + 1;
    if (n * m < 3) n = m = 2;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            mat[i][j] = '0' + (rand() % 2), aux.pb(mp(i, j));

    random_shuffle(aux.begin(), aux.end());
    mat[aux[0].first][aux[0].second] = 'S';
    mat[aux[1].first][aux[1].second] = 'F';
    mat[aux[2].first][aux[2].second] = 'D';

    ofstream fin("delfin.in");

    fin << n << ' ' << m << '\n';
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) fin << mat[i][j];
        fin << '\n';
    }

    fin.close();
}

bool check() {
    run_with_time("./good");
    run_with_time("./brute");

    ifstream fout("delfin.out");
    ifstream fok("delfin.ok");

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

    cin >> tests;
    while(tests--) {
        cerr << tests << ": ";
        genTest();
        if (!check()) return 0;
    }


    return 0;
}
