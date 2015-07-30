#include <cstdio>

using namespace std;
long v,p,s,c,a[500][500],i,gigel,costel,y,total,mi,cost;
int main()
{
freopen("defrag.in","r",stdin);
freopen("defrag.out","w",stdout);
scanf("%ld",&v);
scanf("%ld%ld",&p,&s);
scanf("%ld",&c);
for (i=1; i<=c; i++)
    {
    scanf("%ld%ld",&gigel,&costel);
    a[gigel][costel]=1;
    }
for (i=1; i<=p; i++)
    for (y=1; y<=s; y++)
        a[i][y]+=a[i][y-1];
if (v==1)
    {
    total=0;
    for (i=1; i<=p; i++)
            if (a[i][s]==0)
                total++;
    printf("%ld",total);
    }
if (v==2)
    {
    for (i=1; i<=p; i++)
        {
        total=a[i][s];
        mi=total+56;
        for (y=1; y<=s-total+1; y++)
            {
            cost=total-(a[i][y+total-1]-a[i][y-1]);
            if (mi>cost)
                mi=cost;
            }

        printf("%ld ",mi);

        }
    }

//
//
//for (i=1; i<=p; i++){
//    for (y=1; y<=s; y++)
//        printf("%ld ",a[i][y]);
//    printf("\n");
//}
//
//
return 0;
}
