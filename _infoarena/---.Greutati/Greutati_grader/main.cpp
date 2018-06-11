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

const int maxN = 15;
const int maxP = 15;
const int maxCnt = 35;

int test;

void genTest() {
    ofstream fin("greutati.in");

    int n = (rand() % maxN) + 1;
    int p = maxP;
    vector<int> aux = {};
    int i;

    for (i = 0; i < p; i++) aux.pb(i);
    random_shuffle(aux.begin(), aux.end());
    aux.resize(n);

    fin << n << ' ' << p << '\n';
    for (auto e : aux)
        fin << e << ' ' << (rand() % maxCnt) + 1 << '\n';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("greutati.out");
    ifstream fok("greutati.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Err\n";
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
