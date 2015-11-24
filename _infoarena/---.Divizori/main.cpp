#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxDiv 57

int n, i, dim;
int divs[maxDiv];
int d_pow[maxDiv];
int work[10111];

int main()
{
    freopen("divizori.in", "r", stdin);
    freopen("divizori.out", "w", stdout);

    scanf("%d", &n);
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            divs[++dim] = i;
            while (n % i == 0) {
                n /= i;
                d_pow[dim]++;
            }
        }
    }
    if (n != 1) {
        divs[++dim] = n;
        d_pow[dim] = 1;
    }

    n = 1;
    work[1] = 1;

    for (i = 1; i <= dim; i++) {
        int j, k, lim;
        lim = n;

        int act = 1;
        for (j = 1; j <= d_pow[i]; j++) {
            act *= divs[i];

            if (j & 1) {
                for (k = lim; k > 0; k--)
                    work[++n] = work[k] * act;
            } else {
                for (k = 1; k <= lim; k++)
                    work[++n] = work[k] * act;
            }
        }
    }

    printf("%d\n", n);
    for (i = 1; i <= n; i++)
        printf("%d ", work[i]);

    return 0;
}
