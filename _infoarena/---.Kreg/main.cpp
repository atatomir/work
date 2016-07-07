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

#define maxN 10011

int n, k, i, j;
int gr[maxN];

int main()
{
    freopen("kreg.in","r",stdin);
    freopen("kreg.out","w",stdout);

    scanf("%d%d", &k, &n);
    k /= 2;

    for (i = 0; i < n; i++) {
        for (j = 1; j <= k; j++) {
            printf("%d %d\n", i + 1, 1 + ( (i + j) % n ));
            gr[i + 1]++;
            gr[ 1 + ( (i + j) % n ) ]++;
        }
    }

    for (i = 1; i <= n; i++)
        if (gr[i] != 2 * k)
            cerr << "err";


    return 0;
}
