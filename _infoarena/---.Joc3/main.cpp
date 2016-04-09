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

#define maxN 100011
int n, i, v[maxN];
int xorall;

int p, q;

int main()
{
    freopen("joc3.in","r",stdin);
    freopen("joc3.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    for (i = n - 1; i > 0; i -= 2) xorall ^= v[i];

    if (xorall == 0) {
        printf("-1");
        return 0;
    }

    for (i = n - 1; i > 0; i -= 2) {
        if ( (xorall ^ v[i]) < v[i] ) {
            p = i;
            q = v[i] - (xorall ^ v[i]);
        } else {
            int need = (xorall ^ v[i]) - v[i];
            if (need > 0 && v[i - 1] >= need) {
                p = i - 1;
                q = need;
            }
        }
    }



    printf("%d %d", p, q);


    return 0;
}
