#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

ifstream f("subsecvente.in");
ofstream g("subsecvente.out");
//ID 2
    int v[4][50001],aux[4];
    char a[50001],c;

int min(int x,int y)
{
    if (x<=y)
        return x;
    return y;
}

bool valid (int i,int j,int x,int n1,int n2)
{
    if (v[n1][i]==0 or v[n2][j]==0 or v[n1][i+x]==0 or v[n2][j+x]==0)
        return false;
    for (int k=1;k<x;k++)
    {
        if (v[n1][i+k]!=v[n2][j+k])
            return false;
    }
    return true;
}

int numar (int i, int j,int x,int n1,int n2)
{
    int rez=0;
    for (int k=1;k<x;k++)
        rez+=v[n1][i+k];
    rez+=min(v[n1][i],v[n2][j]);
    rez+=min(v[n1][i+x],v[n2][j+x]);
    return rez;
}

int prog(int n1,int n2)
{
    int x=0;
    int max=0,ok;
    for (int i=0;i<=aux[n1];i++)
    {
        for (int j=0;j<=aux[n2];j++)
        {
            if (i%2==j%2)
            {
                x=0;
                ok=1;
                if (max<min(v[n1][i],v[n2][j]))
                {
                    max=min(v[n1][i],v[n2][j]);
                }
                while (ok==1)
                {
                    x++;
                    if (valid(i,j,x,n1,n2)==false)
                    {
                        ok=0;
                    }
                    else
                    {
                        if (max<numar(i,j,x,n1,n2))
                            max=numar(i,j,x,n1,n2);
                    }
                }
            }
        }
    }
    return max;
}



int main()
{
    int n,nr,k,max;
    f>>n;
    int maxim;
    for (int i=0;i<n;i++)
    {
        k=0;
        nr=0;
        f>>a;
        for (int j=0;j<strlen(a);j++)
        {
            if ((int)a[j]!=(97+k%2))
            {
                v[i][k]=nr;
                k++;
                nr=1;
            }
            else
            {
                nr++;
            }
        }
        v[i][k]=nr;
        aux[i]=k;
    }
    maxim=100;
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            max=prog(i,j);
            if (max<maxim)
            {
                maxim=max;
            }
        }
    }
    g<<maxim;
    f.close();
    g.close();
    return 0;
}
