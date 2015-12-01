#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100111

int n, k, i;
int v[maxN];

void newUser(int pos) {
    v[pos] = 1;
    if(--k == 0) {
        printf("%d", pos);
        cerr << pos;
        exit(0);
    }
}

int main()
{
    freopen("cabine.in","r",stdin);
    freopen("cabine.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    if (v[1] == 0) newUser(1);
    if (v[n] == 0) newUser(n);

    for (i = n - 1; i >= 1; i--)
        if (v[i] == v[i + 1] && v[i + 1] == 0)
            newUser(i);

    for (i = 1; i <= n; i++)
        if (v[i] == 0)
            newUser(i);

    printf("Nimic...");

    return 0;
}
