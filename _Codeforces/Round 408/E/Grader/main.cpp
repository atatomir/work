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

int tests, n, p, k, cnt, i;
vector<int> aux;

void genTest() {
    ofstream fin("test.in");

    p = 1 + (rand() % n);
    k = 1 + (rand() % n);

    fin << n << ' ' << p << ' ' << k << '\n';

    cnt = rand() % n;
    aux.clear(); for (i = 1; i <= n; i++) aux.pb(i);
    random_shuffle(aux.begin(), aux.end());
    aux.resize(cnt);
    sort(aux.begin(), aux.end());
    fin << cnt << ' ';
    for (auto e : aux) fin << e << ' ';
    fin << '\n';

    cnt = rand() % n;
    aux.clear(); for (i = 1; i <= n; i++) aux.pb(i);
    random_shuffle(aux.begin(), aux.end());
    aux.resize(cnt);
    sort(aux.begin(), aux.end());
    fin << cnt << ' ';
    for (auto e : aux) fin << e << ' ';
    fin << '\n';


    fin.close();
}

bool check() {
    system("./good");
    system("./brute");

    ifstream fout("test.out");
    ifstream fok("test.ok");

    int a, b;
    fout >> a;
    fok >> b;

    if (a != b) {
        cerr << "Error\n";
        return false;
    }

    cerr << "Passed\n";
    return true;
}

int main()
{
    srand(time(NULL));

    cin >> tests >> n;
    while (tests--) {
        cerr << "#" << tests << ":";
        genTest();
        if (!check())
            return 0;
    }


    return 0;
}
