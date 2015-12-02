#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, k, i;
int v[maxN];

int qq, p;
int pare;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);

        if (v[i] % 2 == 0) pare++;
        else               continue;

        p = 0;
        while ((v[i] & 1) == 0) {
            p++;
            v[i] >>= 1;
        }

        if (p % 2 == 0) qq++;
    }

    if ( pare % 2 == 0 && qq % 2 == 0)
        printf("Nicky");
    else
        printf("Kevin");



    return 0;
}
