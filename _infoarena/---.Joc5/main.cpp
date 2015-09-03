#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111

int n,i,j,x;
int ans;

int main()
{
    freopen("joc5.in","r",stdin);
    freopen("joc5.out","w",stdout);

    for (scanf("%d",&n); n != 0; scanf("%d",&n)) {
        ans = 0;
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                scanf("%d",&x);
                if (i == j) ans ^= x;
            }
        }

        if (ans > 0)
            printf("1\n");
        else
            printf("2\n");
    }


    return 0;
}
