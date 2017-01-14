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

#define maxN 1024

int t, ti;
int n, i, v[maxN], ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d", &v[i]);

        ans = 0;
        for (i = n; i > 0; i -= 2)
            ans ^= v[i] - v[i - 1];

        if (ans)
            printf("TAK\n");
        else
            printf("NIE\n");
    }



    return 0;
}
