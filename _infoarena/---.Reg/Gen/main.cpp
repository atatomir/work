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

#define def 500000

int test, n, k;

void genTest() {
    ofstream fin("reg.in");

    fin << "1\n";
    fin << rand() % def + 1 << " ";
    fin << rand() % def + 1 << " ";
    fin << rand() % def + 1 << " ";
    fin << n << ' ' << k;


    fin.close();
}

bool check() {
    system("./brute");
    system("./good");

    ifstream fout("reg.out");
    ifstream fok("reg.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "err";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> test >> n >> k;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
