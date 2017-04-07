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
#define ll long long

#define maxN 5011

int n, k, i, a[maxN];
bitset<maxN> B[maxN], aux, mask;
int ans;

bool useful(const bitset<maxN>& b1, const bitset<maxN>& b2, int need) {
    int i, j;

    for (j = 0; j + 1 < k; j++);

    for (i = 0; i < k; i++) {
        if (i + j >= k) j--;

        while (j >= 0) {
            if (b2[j]) break;
            j--;
        }
        if (j < 0) return false;

        if (b1[i] && i + j >= need && i + j < k)
            return true;
    }

    return false;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]), a[i] = min(a[i], k);

    ans = n;
    for (i = 0; i < k; i++) mask[i] = 1;

    B[0][0] = 1;
    for (i = 1; i <= n; i++)
        B[i] = mask & (B[i - 1] | (B[i - 1] << a[i]));

    aux[0] = 1;
    for (i = n; i > 0; i--) {

        if (useful(B[i - 1], aux, k - a[i]))
            ans--;

        aux = mask & (aux | (aux << a[i]));
    }

    printf("%d", ans);


    return 0;
}
