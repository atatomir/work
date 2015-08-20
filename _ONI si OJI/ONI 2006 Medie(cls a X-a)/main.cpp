#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 9011
#define c v[i]
#define b v[j]

int n,i,j,a;
int v[maxN];
int cnt[maxN];
long long ans;

int main()
{
    freopen("medie.in","r",stdin);
    freopen("medie.out","w",stdout);

    scanf("%d",&n);
    for (i = 1; i <= n; i++){
        scanf("%d",&v[i]);
        cnt[ v[i] ]++;
    }

    for (i = 1; i <= n; i++){
        for (j = 1; j < i; j++) {

            //! b+c == 2*a
            a = b+c;
            if ( (a&1) == 0) {
                a >>= 1;
                ans += cnt[a];

                if (c==b) ans -= 2;
            }
        }
    }

    printf("%lld",ans );

    return 0;
}
