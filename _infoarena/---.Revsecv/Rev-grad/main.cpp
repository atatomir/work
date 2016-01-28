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

int test, n, i;

void genTest() {
    //! generate test

    ofstream fin("revsecv.in");

    for (i = 1; i <= n; i++)
        fin << (char)(rand() % 26 + 'a');

    fin.close();
}

bool check() {
    system("./Revsecv");
    system("./Brute");

    long long a, b;

    ifstream fout("revsecv.out");
    ifstream fok("revsecv.ok");

    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "ERROR!\n";
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
