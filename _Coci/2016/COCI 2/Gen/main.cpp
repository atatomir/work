#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int d = 6;

int n, i, j, pos;
int mat[d][d];
vector<int> aux;

bool check() {
    int i, j;
    int s;

    for (i = 0; i < d; i++) {
        s = 0;
        for (j = 0; j < d; j++) s += mat[i][j];
        if (s % d != 0) return false;

        bool found = false;
        for (j = 0; j < d; j++)
            found |= mat[i][j] == s / d;

        if (!found) return false;
    }

    for (i = 0; i < d; i++) {
        s = 0;
        for (j = 0; j < d; j++) s += mat[j][i];
        if (s % d != 0) return false;

        bool found = false;
        for (j = 0; j < d; j++)
            found |= mat[j][i] == s / d;

        if (!found) return false;
    }

    return true;
}

int main()
{

    for (i = 1; i <= d * d; i++) aux.pb(i);
    random_shuffle(aux.begin(), aux.end());

    do {
        pos = 0;
        for (i = 0; i < d; i++)
            for (j = 0; j < d; j++)
                mat[i][j] = aux[pos++];

        if (check()) {
            for (i = 0; i < d; i++, printf("\n"))
                for (j = 0; j < d; j++)
                    printf("%d ", mat[i][j]);
            return 0;
        }
        random_shuffle(aux.begin(), aux.end());
    } while (next_permutation(aux.begin(), aux.end()));

    cerr << "nope";

    return 0;
}
