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

int test, n;
int gr[16011];

void genTest() {
    //! generate test
    ofstream fin("comp.in");

    memset(gr, 0, sizeof(gr));

    fin << n << '\n';
    for (int i = 2; i <= n; i++) {
        int dad = (rand() % (i - 1)) + 1;

        while (gr[dad] == 2)
            dad = (rand() % (i - 1)) + 1;

        gr[dad]++;
        fin << i << ' ' << dad << '\n';
    }


    fin.close();
}

bool check() {
    //! something..
    system("./good");

    int s[3], i, x;
    s[0] = s[1] = s[2] = 0;

    ifstream fin("comp.out");
    for (i = 1; i <= n; i++) {
        fin >> x;
        s[x - 1]++;
    }

    int maxi = max(s[0], max(s[1], s[2]));
    int mini = min(s[0], min(s[1], s[2]));
    int need = (n % 3 == 0 ? 0 : 1);

    if (maxi - mini != need) {
        cerr << "Error\n";
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
