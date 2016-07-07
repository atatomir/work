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

int n, i, dim;
int v[maxN], deep[maxN];

int main()
{
    freopen("aimin.in","r",stdin);
    freopen("aimin.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    deep[dim = 1] = v[1];

    for (i = 2; i <= n; i++) {
        while (dim >= 2 && 1 + max(v[i], deep[dim]) >= deep[dim - 1]) dim--;
        deep[dim] = 1 + max(v[i], deep[dim]);
        deep[++dim] = v[i];
    }

    printf("%d", deep[1]);


    return 0;
}
