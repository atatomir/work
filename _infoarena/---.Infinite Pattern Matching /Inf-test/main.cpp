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

#define maxN 200

int n, i, pos, x;
char ch[maxN];
char ini[15000000];
vector<char> aux;

int main()
{
    ifstream fin("infinitepatternmatching.in");
    ifstream fout("infinitepatternmatching.out");

    fout >> n;
    for (i = 1; pos < n; i++) {
        aux.clear();

        x = i;
        while (x) {
            aux.pb(x % 2);
            x >>= 1;
        }

        while (!aux.empty()) {
            ch[++pos] = aux[aux.size() - 1] + '0';
            aux.pop_back();
        }
    }

    cerr << ch + 1 << '\n';

    pos = n;
    fin >> ini + 1;
    n = strlen(ini + 1);

    for (i = 1; i <= n; i++)
        if (ch[pos - i + 1] != ini[n - i + 1])
            cerr << "Err";

    return 0;
}
