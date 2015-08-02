#include <iostream>                //Problema 2 Fractii
#include <fstream>
#include <math.h>

using namespace std;

int p,n,st[100];

ifstream f("fractii2.in");
ofstream out("fractii2.out");

int valid (int k)
{
    int i;
    for (i=1; i<=n; i++)
        if (st[k]==st[i])
            return 1;
    return 0;
}

void afisare ()
{
    int i;
    for (i=1; i<=n; i++)
        cout<<st[i]<<' ';
    cout<<endl;
}

void solutie ()
{
    int i,a,r,c[100],pl[100],g=0;
    float s=0;
    for (i=1; i<=n; i++)
        pl[i]=pow (2,st[i]);

    for (i=1; i<n && g==0; i++)
    {
        if (pl[i]==pl[i+1])
            g=0;
        else
            g=1;
    }

    if (g==1)
    {
        for (i=1; i<=n; i++)
            c[i]=1;
        a=st[1];
        for (i=1; i<n; i++)
            a=max (a , st[i+1]);
        for (i=1; i<=n; i++)
        {
            if (st[i]!=a)
            {
                r=a/st[i];
                st[i]=r*st[i];
                c[i]=r*c[i];
            }
            s+=c[i];
        }
        if (s/a==1)
            for (i=1; i<=n; i++)
                out<<st[i]<<' ';
    }
    else
        if (n/pl[1]==1)
            for (i=1; i<=n; i++)
                out<<st[i]<<' ';
}

void back (int k)
{
    if (k==n+1)
    {
        solutie ();
        k=1;
        back (k);
    }
    else
    {
        if (st[k]<n)                //Am uitat Backtracking !!!!!!!!!!!!
        {
            st[k]++;
            if (valid (k))
            {
                k++;
                back (k);
            }
        }
        else
            k--;
    }
}

int main()
{
    f>>p>>n;
    back (1);
}
