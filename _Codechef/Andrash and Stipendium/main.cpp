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

int t, ti;
int n, i, x, sum;
bool good = true;
bool any_full;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);

        good = true;
        any_full = false;
        sum = 0;

        for (i = 1; i <= n; i++) {
            scanf("%d", &x);
            sum += x;
            if (x == 2) good = false;
            if (x == 5) any_full = true;
        }

        good &= any_full;
        if (sum < n * 4) good = false;
        if (good)
            printf("Yes\n");
        else
            printf("No\n");
    }


    return 0;
}
