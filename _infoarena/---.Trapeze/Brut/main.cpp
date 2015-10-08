#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int n, i, j, aux, ans;
int first_v[100];

bool works(int x, int dim) {
    x *= 2;

    if (x % dim != 0) return false;
    x /= dim;
    x -= dim - 1;

    if (x <= 0) return false;
    if (x % 2 == 1) return false;

    aux++;
    return true;
}

int main()
{
    cin >> n;
    cerr << "----------------------------\n";

    for (i = 1; i <= n; i++) {
        aux = 0;

        cerr << i << " | ";
        for (j = 1; j <= i; j++)
            if (works(i, j))
                cerr << j << ' ';

        printf("\n");
        ans = max(ans, aux);

        if (first_v[aux] == 0) first_v[aux] = i;
    }

    for (i = 1; i <= 10; i++) cerr << "f " << i << ' ' << first_v[i] << '\n';


    return 0;
}
