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

int n, i;
int x, act;

int main()
{
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);

    for (int t = 1; t <= 10; t++) {
        scanf("%d", &n);
        act = 0;

        for (i = 1; i <= n; i++) {
            scanf("%d", &x);
            act ^= x & 3;
        }

        if (act)
            printf("1\n");
        else
            printf("0\n");
    }


    return 0;
}
