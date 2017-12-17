#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 9;

int tests, n, i;
vector<int> perm;

void gen_test() {
    n = 1 + (rand() % maxN);

    ofstream fin("test.in");

    fin << n << '\n';

    perm = {};
    for (i = 1; i <= n; i++) perm.pb(i);
    random_shuffle(perm.begin(), perm.end());

    for (auto e : perm) {
        if (rand() % 2)
            fin << e << ' ';
        else
            fin << "0 ";
    }


    fin.clear();
}

bool check() {
    system("./brute");
    system("./good");
    ifstream fout("test.out");
    ifstream fok("test.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a != b) return false;
    return true;
}

int main()
{

    cin >> tests;
    while (tests--) {
        gen_test();
        cerr << tests << ' ';
        if (!check()) {
            cerr << "Error";
            return 0;
        }
        cerr << "OK" << '\n';
    }


    return 0;
}
