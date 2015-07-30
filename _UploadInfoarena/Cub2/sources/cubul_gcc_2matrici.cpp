///prof. Gorea Claudiu-Cristian
///C.N. Al. Papiu Ilarian Tg-Mures
#include <fstream>
using namespace std;
ifstream fin ("cub2.in");
ofstream fout("cub2.out");
int a[201][201],b[201][201];
int p,n,v,i,j,x,k,sum,f1,f2,f3,f4,nr;
int prim(int m)
{
    int d;
    if (m<2 ||(m>2 && m%2==0)) return 0;
    for(d=2;d*d<=m;d++)
        if(m%d==0) return 0;
    return 1;
}
void afisare(int mat[201][201])
{
    int l,c;
    for(l=1;l<=n;l++)
    {
        for(c=1;c<=n;c++)
            fout<<mat[l][c]<<" ";
        fout<<endl;
    }
    fout<<"---------------------\n";
}
int main()
{
    fin>>p;
    fin>>n>>v;
///nivel 1 - matrice A
    x=1;
    k=0;
    while(x<=n/2)
    {
        ///spre stanga - linia x
        for(j=x;j<=n-x;j++)
            a[x][j]=++k;
        ///spre jos - coloana n-x+1
        for(i=x;i<=n-x;i++)
            a[i][n-x+1]=++k;
        ///spre stanga - linia n-x+1
        for(j=n-x+1;j>x;j--)
            a[n-x+1][j]=++k;
        ///spre sus - coloana x
        for(i=n-x+1;i>x;i--)
            a[i][x]=++k;
        x++;
    }
    if (n%2==1) a[n/2+1][n/2+1]=++k;
    //afisare(a);
///nivel 2 - matrice B
    sum=2*n*n+1;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            b[i][j]=sum-a[i][j];
    //afisare(b);
    if (p==1)
    {
        ///cerinta 1
        x=v;
        int nivel=0;
        while(x>2*n*n)
            x=x-2*n*n, nivel+=2;
        int stop=0;
        for(i=1;i<=n && stop==0; i++)
            for(j=1;j<=n && stop==0; j++)
            {
                if(a[i][j]==x)
                {
                    fout<<i<<" "<<j<<" "<<nivel+1<<endl;
                    stop=1;
                }
                if(b[i][j]==x)
                {
                    fout<<i<<" "<<j<<" "<<nivel+2<<endl;
                    stop=1;
                }
            }
    }
    else
    {
        ///cerinta 2
        f1=f2=f3=f4=0;
        ///fata 1 - linia 1 A,B,.... 200*200 elemente=40.000 nr de testat
        for(j=1;j<=n;j++)
        {
            nr=a[1][j];
            while(nr<n*n*n)
            {
                if (prim(nr)) f1++;
                nr+=2*n*n;
            }
            nr=b[1][j];
            while(nr<n*n*n)
            {
                if (prim(nr)) f1++;
                nr+=2*n*n;
            }
        }
        ///fata 2 - coloana n A,B,....
        for(i=1;i<=n;i++)
        {
            nr=a[i][n];
            while(nr<n*n*n)
            {
                if (prim(nr)) f2++;
                nr+=2*n*n;
            }
            nr=b[i][n];
            while(nr<n*n*n)
            {
                if (prim(nr)) f2++;
                nr+=2*n*n;
            }
        }
        ///fata 3 - linia n A,B,....
        for(j=1;j<=n;j++)
        {
            nr=a[n][j];
            while(nr<n*n*n)
            {
                if (prim(nr)) f3++;
                nr+=2*n*n;
            }
            nr=b[n][j];
            while(nr<n*n*n)
            {
                if (prim(nr)) f3++;
                nr+=2*n*n;
            }
        }
        ///fata 4 - coloana 1 A,B,....
        for(i=1;i<=n;i++)
        {
            nr=a[i][1];
            while(nr<n*n*n)
            {
                if (prim(nr)) f4++;
                nr+=2*n*n;
            }
            nr=b[i][1];
            while(nr<n*n*n)
            {
                if (prim(nr)) f4++;
                nr+=2*n*n;
            }
        }
        fout<<f1<<'\n';
        fout<<f2<<'\n';
        fout<<f3<<'\n';
        fout<<f4<<'\n';
    }

    return 0;
}
