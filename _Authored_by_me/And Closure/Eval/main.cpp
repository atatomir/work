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

#define limit 1000000

int test, n, i;

void genTest() {
    //! generate test
    ofstream fin("test.in");

    fin << n << '\n';
    for (i = 1; i <= n; i++)
        fin << rand() % limit << ' ';


    fin.close();
}

bool check() {
    system("./brute");
    system("./good");

    ifstream fout("test.out");
    ifstream fok("test.ok");

    int a, b, nr;

    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "error 1\n";
        return false;
    }

    nr = a;
    for (int i = 1; i <= nr; i++) {
        fout >> a;
        fok >> b;

        if (a != b) {
            cerr << "error 2\n";
            return false;
        }
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
