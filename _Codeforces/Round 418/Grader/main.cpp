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
    ofstream fin("test.in");

    fin << n << '\n';
    for (i = 1; i <= n; i++) fin << (rand() % 2) + 2 << ' ';

    fin.close();
}

bool check() {
    //! something..
    system("./brute");
    system("./good");

    ifstream fout("test.out");
    ifstream fok("test.ok");

    int a, b;
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

    //! read t, n, ....
    cin >> test >> n;

    for (; test; test--) {
        genTest();

        cerr << "#" << test << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
