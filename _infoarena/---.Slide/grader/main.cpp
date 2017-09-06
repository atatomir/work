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
#define ll long long

int test, n, i;

void genTest() {
    //! generate test
    ofstream fin("slide.in");

    for (i = 1; i <= n; i++) {
        int v = rand() % 3;
        if (v == 0) fin << "@";
        if (v == 1) fin << "#";
        if (v == 2) fin << ".";
    }

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("slide.out");
    ifstream fok("slide.ok");

    ll a, b;
    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Error";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> test >> n;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
