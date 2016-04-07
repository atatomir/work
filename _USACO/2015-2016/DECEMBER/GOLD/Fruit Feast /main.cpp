#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10000111

int T, A, B, i;
bitset<maxN> work;

void solve() {
    int i;

    for (i = A; i <= T; i++)
        work[i] = work[i] | work[i - A];
    for (i = B; i <= T; i++)
        work[i] = work[i] | work[i - B];
}

int main()
{
    freopen("feast.in","r",stdin);
    freopen("feast.out","w",stdout);

    scanf("%d%d%d", &T, &A, &B);

    work.reset();
    work[0] = 1;

    solve();

    for (i = 1; i <= T; i++)
        work[i] = work[i] | work[i * 2] | work[i * 2 + 1];

    solve();

    for (i = T; i >= 0; i--) {
        if (work[i] == 1) {
            printf("%d", i);
            return 0;
        }
    }

    return 0;
}
