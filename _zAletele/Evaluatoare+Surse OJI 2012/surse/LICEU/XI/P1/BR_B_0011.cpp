#include<stdio.h>
#include<math.h>
int n,a[2][10005],i,s1[10005],s2[10005],nrmin,poz1[2][10005],poz2[2][10005],nrc,sc[10005],nrperm,nrc1,nrp;
int viz[2][10005],a1[2][10005],k,j;
int main()
{
    freopen("biperm.in","r",stdin);
    freopen("biperm.out","w",stdout);
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[0][i]);
        s1[a[0][i]]++;
        poz1[s1[a[0][i]]-1][a[0][i]]=i;
        if(s1[a[0][i]]==2)
            nrmin++;
    }
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[1][i]);
        s2[a[1][i]]++;
        poz2[s2[a[1][i]]-1][a[1][i]]=i;
    }
    nrc1=1;
    for(i=0;i<n;i++)
    {
        if(viz[0][a[0][i]]==0 && viz[1][a[1][i]]==0)
        {
            a1[0][i]=a[0][i];
            a1[1][i]=a[1][i];
            viz[0][a[0][i]]=1;
            viz[1][a[1][i]]=1;
        }
        else
            {
                a1[0][i]=a[1][i];
                a1[1][i]=a[0][i];
                viz[0][a[1][i]]=1;
                viz[1][a[0][i]]=1;
            }
    }
    nrperm=pow(2,n-nrmin*2-1);
    printf("%d %d\n",nrperm,nrmin);
    for(i=0;i<n;i++)
        printf("%d ",a1[0][i]);
    printf("\n");
    for(i=0;i<n;i++)
        printf("%d ",a1[1][i]);
    return 0;
}
