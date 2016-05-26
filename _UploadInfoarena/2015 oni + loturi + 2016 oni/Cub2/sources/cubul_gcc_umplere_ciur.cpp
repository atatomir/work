///prof. Gorea Claudiu-Cristian
///C.N. Al. Papiu Ilarian Tg-Mures
#include <cstdio>
using namespace std;
int a[101][101][101],n,v,l,c,x,y,z,nivel,i,j,k,colt,lim,p;
bool ciur[1000001];
int f1,f2,f3,f4;
void afisare()
{
    int i,j;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            printf("%4d",a[i][j][nivel]);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    freopen ("cub2.in","r",stdin);
    freopen ("cub2.out","w",stdout);
    scanf("%d",&p);
    scanf("%d %d",&n,&v);

    nivel=0;
    k=0;
    ciur[1]=ciur[0]=true; /// adica nu e prim;
    for(i=2;i<=n*n*n;i++)
        if (ciur[i]==false)
            for(j=2;j<=n*n*n/i;j++)
                ciur[i*j]=true;

    f1=f2=f3=f4=0;
/// SE COMPLETEAZA INTREGUL CUB
    while(nivel<n)
    {
        nivel++;
        ///nivel impar - plec din 1,1
        l=c=1;
        while(l<=n/2)
        {
            ///dir1
            for(j=c;j<=n-c;j++)
            {
                k++;
                a[l][j][nivel]=k;
                if (k==v && p==1) printf("%d %d %d\n",l,j,nivel);
            }
            ///dir2
            for(i=l;i<=n-l;i++)
            {
                k++;
                a[i][n-c+1][nivel]=k;
                if (k==v && p==1) printf("%d %d %d\n",i,n-c+1,nivel);
            }
            ///dir3
            for(j=n-c+1;j>c;j--)
            {
                k++;
                a[n-l+1][j][nivel]=k;
                if (k==v && p==1) printf("%d %d %d\n",n-l+1,j,nivel);
            }
            ///dir4
            for(i=n-l+1;i>l;i--)
            {
                k++;
                a[i][c][nivel]=k;
                if (k==v && p==1) printf("%d %d %d\n",i,c,nivel);
            }
            l++;
            c++;
        }
        if (n%2==1)
        {
            k++;
            a[n/2+1][n/2+1][nivel]=k;
            if (k==v && p==1) printf("%d %d %d\n",n/2+1,n/2+1,nivel);
        }
       // afisare();
        if (nivel<n)
        {
            colt=a[1][1][nivel];
            nivel++;  /// nivelul par
            lim=colt+n*n*2;
            for(i=1;i<=n;i++)
                for(j=1;j<=n;j++)
                    {
                        a[i][j][nivel]=(colt-1)+lim-a[i][j][nivel-1];
                        if (a[i][j][nivel]==v && p==1)
                            printf("%d %d %d\n",i,j,nivel);
                    }
            k+=n*n;
           // afisare();
        }
    }
    ///fata 1
    for(nivel=1;nivel<=n;nivel++)
        for(j=1;j<=n;j++)
            if(ciur[a[1][j][nivel]]==false)
            {
              //  printf("%d ",a[1][j][nivel]);
                f1++;
            }
    if (p==2) printf("%d\n",f1);
    ///fata 2
    for(nivel=1;nivel<=n;nivel++)
        for(i=1;i<=n;i++)
            if(ciur[a[i][n][nivel]]==false)
            {
              //  printf("%d ",a[i][n][nivel]);
                f2++;
            }
    if (p==2) printf("%d\n",f2);
    ///fata 3
    for(nivel=1;nivel<=n;nivel++)
        for(j=1;j<=n;j++)
            if(ciur[a[n][j][nivel]]==false)
            {
              //  printf("%d ",a[n][j][nivel]);
                f3++;
            }
    if (p==2) printf("%d\n",f3);
    ///fata 4
    for(nivel=1;nivel<=n;nivel++)
        for(i=1;i<=n;i++)
            if(ciur[a[i][1][nivel]]==false)
            {
               // printf("%d ",a[i][1][nivel]);
                f4++;
            }
    if (p==2) printf("%d\n",f4);
    return 0;
}
