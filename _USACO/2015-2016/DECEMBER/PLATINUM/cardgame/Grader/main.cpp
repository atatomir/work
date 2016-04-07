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

int tests, n, i;
vector<int> useful;

void genTest() {
    ofstream fin("cardgame.in");

    fin << n << '\n';
    random_shuffle(useful.begin(), useful.end());
    for (i = 0; i < useful.size() / 2; i++)
        fin << useful[i] << ' ';

    fin.close();
}

bool check() {
    system("./Brute");
    system("./cardgame");

    ifstream fout("cardgame.out");
    ifstream fok("cardgame.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a == b)
        printf("Passed\n");
    else
        printf("Error\n");

    return a == b;
}

int main()
{
    cin >> tests >> n;

    for (i = 1; i <= 2 * n; i++)
        useful.pb(i);

    for (; tests > 0; tests--) {
        genTest();

        cerr << "#" << tests << " : ";
        if (!check())
            return 0;
    }

    return 0;
}
