#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

int n, i;
unordered_map<int, bool> H;

void genTest() {
    ofstream fin("meandian.in");
    H.clear();

    n = 50;
    fin << n << ' ';
    for (i = 1; i <= n; i++) {
        int v = (rand() % 50000) * 2;

        while (H[v]) v = (rand() % 50000) * 2;
        H[v] = true;
        fin << v << ' ';
    }

    fin.clear();
}

bool check() {
    system("./Meandian");

    ifstream fout("meandian.out");
    fout >> n;

    if (n == 0) {
        cerr << "Error!";
        return false;
    }

    cerr << "Passed\n";

    return true;
}

int main()
{
    int tests;
    for (cin >> tests; tests > 0; tests--) {
        cerr << "#" << tests << " ";

        genTest();
        if (!check())
            return 0;
    }


    return 0;
}
