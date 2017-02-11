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

int n, i;
int a[maxN];

int cmmdc(int a, int b) {
    if (a < b) swap(a, b);

    while (b != 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

bool solve() {
    int i;
    int even, odd, aux;

    even = odd = 0;
    for (i = 1; i <= n; i++) {
        if (a[i] & 1)
            odd++;
        else
            even++;
    }

    if (even & 1)
        return true;

    if (odd >= 2)
        return false;

    if (odd != 1) cerr << "error";

    for (i = 1; i <= n; i++) {
        if (a[i] & 1) {
            a[i] ^= 1;
            if (a[i] == 0) return false;
        }
    }

    aux = a[1];
    for (i = 2; i <= n; i++) aux = cmmdc(aux, a[i]);
    for (i = 1; i <= n; i++) a[i] /= aux;

    return !solve();
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);

    if (solve())
        printf("First\n");
    else
        printf("Second\n");


    return 0;
}
