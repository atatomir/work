#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int t;
int x,y;
int le,ri;

int main()
{
    freopen("cazino.in","r",stdin);
    freopen("cazino.out","w",stdout);

    for (scanf("%d",&t); t; t--) {
        scanf("%d%d",&x,&y);

        if (x == y) {
            printf("1.00000");
            continue;
        }

        le = x / 2;
        ri = (y - x + 1) / 2;

        printf("%.5lf\n",1.0*le/(le+ri));
    }


    return 0;
}
