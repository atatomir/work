#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int limit = 1000000;
int test, n, i;

void genTest() {
    //! generate test
    ofstream fin("test.in");

    fin << n << '\n';
    for (i = 1; i <= n; i++)
        fin << (rand() % limit) << ' ';

    fin.close();
}

void customTest() {
    //! generate test
    ofstream fin("test.in");

    vector<int> aux;
    aux.clear();

    fin << n << '\n';
    /*for (i = 1; i <= n; i++) {
        if (rand() % 10 <= 8 && !aux.empty()) {
            int act = aux[rand() % aux.size()];
            fin << act << ' ';
        } else {
            int act = rand() % limit;
            fin << act << ' ';
            aux.pb(act);
        }

    }*/

    /*for (i = 1; i <= n; i++) {
        int act = 0;
        int cnt;

        if (rand() % 5 == 0) act = rand() % limit;
        cnt = rand() % 10;
        while (cnt-- && aux.empty() == false)
            act |= aux[ rand() % aux.size() ];

        while (act > limit) act >>= 1;

        aux.pb(act);
        fin << act << ' ';
    }*/

    for (i = 1; i <= 16; i++) aux.pb(1 << i);
    for (int conf = 1; conf < (1 << 16); conf++) {
        int act = 0;

        for (int j = 0; j < 16; j++)
            if (conf & (1 << j))
                act |= aux[j];

        fin << act << ' '; n--;
    }

    if (n < 0) cerr << "err";
    while (n > 0) fin << rand() % limit << ' ', n--;

    /*for (i = 1; i <= n; i++)
        if (rand() % 2 == 0)
            fin << ((rand() % limit) | 771 ) << ' ';
        else
            fin << ((rand() % limit) | (rand() % 13) ) << ' ';*/

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

    /*nr = a;
    for (int i = 1; i <= nr; i++) {
        fout >> a;
        fok >> b;

        if (a != b) {
            cerr << "error 2\n";
            return false;
        }
    }*/

    cerr << "Passed\n";
    return true;
}

void move_test(int id) {
    string a = "Tests/test-" + to_string(id) + ".in";
    string b = "Tests/test-" + to_string(id) + ".ok";

    rename("test.in", a.c_str());
    rename("test.out", b.c_str());
}



int main()
{
    srand(time(NULL));

    for (int id = 36; id <= 39; id++) {
        n = 100000;
        limit = 1000000;

        genTest();
        //customTest();

        if(!check()) return 0;
        move_test(id);
    }



    return 0;
}
