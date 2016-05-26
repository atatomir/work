#include <cstdio>
#include <algorithm>
 
using namespace std;
 
#define maxn 200010
#define inf (1LL*1000000000*1000000000)
 
int n, m, tip;
long long v[maxn];
 
int main()
{
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
 
    scanf("%d%d", &n, &m);
 
    for(int i=1; i<=n; ++i)
        v[i]=-inf;
 
    for(int pas=1; pas<=m; ++pas)
    {
        scanf("%d", &tip);
        if(tip==1)
        {
            int poz;
            long long panta, varf;
 
            scanf("%d%lld%lld", &poz, &varf, &panta);
 
            for(int j=poz; j>0; --j)
            {
                if(v[j] <= varf - panta * (poz-j))
                    v[j] = varf - panta * (poz-j);
                else
                {
                 //   printf("!%d ", j+1);
                    break;
                }
            }
 
            for(int j=poz+1; j<=n; ++j)
            {
                if(v[j] <= varf - panta * (j-poz))
                    v[j] = varf - panta * (j-poz);
                else
                {
                //    printf("%d", j-1);
                    break;
                }
            }
        }
        else
        {
            int l, r;
            long long ans=inf;
 
            scanf("%d%d", &l, &r);
 
            for(int j=l; j<=r; ++j)
                ans=min(ans, v[j]);
 
            printf("%lld\n", ans);
        }
    }
 
    return 0;
}
