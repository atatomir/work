#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back

int tests, n, g, i;

void getTest() {
    ofstream fin("ghiozdan.in");
    fin << n << ' ' << g << '\n';
    for (i = 1; i <= n; i++)
        fin << rand() % 200 + 1 << '\n';
}

bool check() {
    system("./Brute");
    system("./Ghiozdan");

    ifstream fout("ghiozdan.out");
    ifstream fok("ghiozdan.ok");

    int nn1, nn2, gg1, gg2;
    fout >> nn1 >> gg1;
    fok >> nn2 >> gg2;

    if (nn1 != nn2 || gg1 != gg2) {
        cout << "Error!\n";
        return false;
    }

    cout << "Passed!\n";
    return true;

}

int main()
{
    srand(time(NULL));

    cin >> tests >> n >> g;
    while (tests--) {
        getTest();

        cout << "#" << tests << " : ";
        if (!check())
            return 0;
    }



    return 0;
}
