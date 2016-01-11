#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxDim 100

int n, k, i, tests;
map< pair<int, int>, bool> M;

void genTest() {
    ofstream fin("popandai.in");

    fin << n << ' ' << k << '\n';
    for (int i = 1; i <= n; i++) {
        int xx = rand() % maxDim;
        int yy = rand() % maxDim;

        while (M[ mp(xx, yy) ] == true) {
            xx = rand() % maxDim;
            yy = rand() % maxDim;
        }
        M[mp(xx, yy)] = true;
        fin << xx << ' ' << yy<< '\n';
    }

    fin.close();
}

bool check() {
    double a, b;

    system("./Popandai");
    system("./Brute");
    ifstream fout("popandai.out");
    ifstream fok("popandai.ok");

    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Error !\n";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    cin >> tests;
    cin >> n >> k;

    srand(time(NULL));

    for (;tests > 0; tests--) {
        genTest();

        cerr << "#" << tests << " : ";

        if (!check())
            return 0;
    }



    return 0;
}
