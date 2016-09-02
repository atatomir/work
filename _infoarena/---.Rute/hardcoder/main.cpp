#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int i, dim;
char s[333];

int main()
{

    ofstream sol("sol");

    sol << "const string[30] = {";
    for (i = 1; i <= 30; i++) {
        ofstream fin("rute.in");
        fin << i;
        fin.close();

        system("./Rute");

        ifstream fout("rute.out");
        fout >> s + 1;
        dim = strlen(s + 1);

        sol << '"';
        for (int j = 1; j <= dim; j++) sol << s[j];
        sol << '"';
        if (i != 30) sol << ", ";
    }

    sol << "};";


    sol.close();

    return 0;
}
