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

int t, ti, x;
int n, i, xoro, cnt;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        xoro = cnt = 0;
        for (i = 1; i <= n; i++) {
            scanf("%d", &x);
            xoro ^= x;
            if (x == 1) cnt++;
        }

        if (cnt == n) {
            if (cnt & 1)
                printf("Brother\n");
            else
                printf("John\n");
        } else {
            if (xoro == 0)
                printf("Brother\n");
            else
                printf("John\n");
        }
    }


    return 0;
}
