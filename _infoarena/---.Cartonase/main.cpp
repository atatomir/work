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

int t, i, n;
int v;
char c;

int main()
{
    freopen("cartonase.in","r",stdin);
    freopen("cartonase.out","w",stdout);

    scanf("%d", &t);
    for (; t; t--) {
        scanf("%d", &n);
        v = 0;

        for (i = 1; i <= n; i++) {
            scanf(" %c", &c);
            if (c == 'R') v ^= i;
        }

        if (v)
            printf("DA\n");
        else
            printf("NU\n");
    }


    return 0;
}
