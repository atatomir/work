#include <iostream>
#include <fstream>
using namespace std;
bool marcare[1001][1001];
short a[1001][1001],dame[101],gri[51];
int main()
{
    int i,j,n,d,k,c,p,z,x,y,max,max1,M;
    ifstream f("betasah.in");
    ofstream g("betasah.out");
    f>>n>>d>>k;
    for (i=1;i<=n;i++)
    for (j=1;j<=n;j++)
    {
        a[i][j]=1;
        if (j==i)
        break;
    }
    for (i=1;i<=d*2;i++)
    f>>dame[i];
    for (i=1;i<d*2;i=i+2)
    for (j=i+2;j<=d*2;j=j+2)
    if (dame[i]>dame[j]||(dame[i]==dame[j]&&dame[i+1]>dame[j+1]))
    {
        z=dame[i];
        dame[i]=dame[j];
        dame[j]=z;
        z=dame[i+1];
        dame[i+1]=dame[j+1];
        dame[j+1]=z;
    }
    for (i=1;i<=k*2;i++)
    f>>gri[i];
    for (i=1;i<k*2;i=i+2)
    for (j=i+2;j<=k*2;j=j+2)
    if (gri[i]>gri[j]||(gri[i]==gri[j]&&gri[i+1]>gri[j+1]))
    {
        z=gri[i];
        gri[i]=gri[j];
        gri[j]=z;
        z=gri[i+1];
        gri[i+1]=gri[j+1];
        gri[j+1]=z;
    }
    x=y=1;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
        {
            if (dame[x]==i&&dame[x+1]==j)
            {
                a[i][j]=2;
                x=x+2;
            }
            if (gri[y]==i&&gri[y+1]==j)
            {
                a[i][j]=0;
                y=y+2;
            }
            if (i==j)
            break;
        }
    // Am creat matricea
    p=0;
    for (c=1;c<=d;c++)            // Piesa
    {
        for (i=1;i<=n;i++)        // Linia
        for (j=1;j<=n;j++)        // Coloana
        {
            if (a[i][j]==2)
            {
                if (a[i-1][j]==1&&marcare[i-1][j]!=1)
            {
                ++p;marcare[i-1][j]=1;
                for (x=i-2;x>=1;x--)
                if (a[x][j]==1&&marcare[x][j]!=1)
                {++p;marcare[x][j]=1;}
                else
                break;
            }
            if (a[i-1][j+1]==1&&marcare[i-1][j+1]!=1)
            {
                ++p;marcare[i-1][j+1]=1;
                for (x=i-2;x>=1;x--)
                for (y=j+2;j<=n;j++)
                {if (a[x][y]==1&&marcare[x][y]!=1)
                {++p;marcare[x][y]=1;}
                break;}
            }
            if (a[i][j+1]==1&&marcare[i][j+1]!=1)
            {
                ++p;marcare[i][j+1]=1;
                for (x=j+2;x<=n;x++)
                if (a[i][x]==1&&marcare[i][x]!=1)
                {++p;marcare[i][x]=1;}
                else
                break;
            }
            if (a[i+1][j+1]==1&&marcare[i+1][j+1]!=1)
            {
                ++p;marcare[i+1][j+1]=1;
                for (x=i+2;x<=n;x++)
                for (y=y+2;y<=n;y++)
                {if (a[x][y]==1&&marcare[x][y]!=1)
                {++p;marcare[x][y]=1;}
                break;}
            }
            if (a[i+1][j]==1&&marcare[i+1][j]!=1)
            {
                ++p;marcare[i+1][j]=1;
                for (x=i+2;x<=n;x++)
                if (a[x][j]==1&&marcare[x][j]!=1)
                {++p;marcare[x][j]=1;}
                else
                break;
            }
            if (a[i+1][j-1]==1&&marcare[i+1][j-1]!=1)
            {
                ++p;marcare[i+1][j-1]=1;
                for (x=i+2;x<=n;x++)
                for (y=j-2;y>=1;y--)
                {
                    if (a[x][y]==1&&marcare[x][y]!=1)
                    {++p;marcare[x][y]=1;}
                    break;
                }
            }
            if (a[i][j-1]==1&&marcare[i][j-1]!=1)
            {
                ++p;marcare[i][j-1]=1;
                for (x=j-2;x>=1;x--)
                if (a[i][x]==1&&marcare[i][x]!=1)
                {++p;marcare[i][x]=1;}
                else
                break;
            }
            if (a[i-1][j-1]==1&&marcare[i-1][j-1]!=1)
            {
                ++p;marcare[i-1][j-1]=1;
                for (x=i-2;x>=1;x--)
                for (y=j-2;y>=1;y--)
                {
                    if (a[x][y]==1&&marcare[x][y]!=1)
                    {++p;marcare[x][y]=1;}
                    break;
                }
            }
        }
        if (i==j)
        break;
    }
    }
    max1=0;
    for (i=1;i<=n;i++)
    {
        max=0;
        for (j=1;j<=n;j++)
        {if (a[i][j]==1||a[i][j]==2)
        ++max;
        if (i==j)
        break;
        }
        if (max>max1||max==max1)
        {max1=max;M=i;}
    }
    g<<M<<'\n'<<p<<'\n';
    f.close();
    g.close();
    return 0;
}
