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

const int maxN = 9;

int test, n, m, i;
string s;

void genTest() {
    ofstream fin("karma.in");

    n = (rand() % maxN) + 1;
    m = (rand() % maxN) + 1;
    if (m & 1) m++;

    fin << n << ' ' << m << '\n';

    s = "";
    for (i = 1; i <= m / 2; i++) s.pb('(');
    for (i = 1; i <= m / 2; i++) s.pb(')');

    for (i = 1; i <= n; i++) {
        random_shuffle(s.begin(), s.end());
        fin << s << '\n';
    }

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("karma.out");
    ifstream fok("karma.ok");

    int a, b;

    fout >> a;
    fok >> b;
    cerr << a << ' ';

    if (a != b) {
        cerr << "Error\n";
        return false;
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
