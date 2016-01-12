#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back

int tests, cases, n, i;
char a;
char b;

void genTest() {
    ofstream fin("input.in");

    fin << cases << '\n';
    for (int i = 1; i <= cases; i++) {
        int act = rand() % n + 1;
        fin << act << ' ' << rand() % 1000000000 << '\n';

        for (int j = 1; j <= act; j++)
            fin << rand() % 1000000000 << ' ';
        fin << '\n';
    }

    fin.close();
}

bool check() {
    system("./good");
    system("./Brute");

    ifstream fout("output.out");
    ifstream fok("output.ok");

        a = '!';

        for (int j = 0; j <= 1000; j++) {
            fout >> a;
            fok >> b;

            if (a != b) {
                cerr << "Error";
                return false;
            }

        }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> tests >> cases >> n;
    for (i = 1; i <= tests; i++) {
        genTest();

        cout << "#" << i << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
