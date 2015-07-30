#include <iostream>
#include<fstream>
using namespace std;
int main()
{
    ifstream f("cool.in");
    ofstream g("cool.out");
    int p, n, k, kk, a[1000], v[1000], u[1000], i, j, aux, nr, nr1, ok, q;
    f>>p>>n>>k;
    for (i=1; i<=n; i++)
        f>>a[i];
    if (p==1)
    {
        for (i=1; i<=k; i++)
           v[i]=a[i];
        for (i=1; i<k; i++)
           for (j=i+1; j<=k; j++)
             if (v[i]>v[j])
             {
                 aux=v[i];
                 v[i]=v[j];
                 v[j]=aux;
             }
        ok=1;
        for (i=1; i<k and ok==1; i++)
           if (v[i]+1!=v[i+1])
              ok=0;
        if (ok==1)
            g<<v[k];
        else
           {
               nr=0;
               for (i=1; i<=v[k]; i++)
                   u[i]=0;
               for (i=1; i<=k; i++)
                  u[v[i]]++;
               for (i=1; i<=k; i++)
                  if (u[v[i]]==1)
                    nr++;
                g<<nr;
           }
    }
    else
    {
        nr=0; nr1=0;
        for (i=n; i>=1 and nr==0; i--)
        {
            kk=1;
            while (i+kk-1<=n)
            {
                for (j=kk; j<=i+kk-1; j++)
                    u[j]==a[j];
                for (j=kk; j<i+kk-1; j++)
                   for (q=j+1; q<=j+kk-1; q++)
                      if (u[j]>u[q])
                      {
                          aux=u[j];
                          u[j]=u[q];
                          u[q]=aux;
                      }
                ok=1;
                for (j=1; j<=i+kk-1; j++)
                   if (u[j]+1!=u[j+1])
                      ok=0;
                if (ok==1)
                {
                    nr1=5;
                    nr++; kk++;
                }
                else
                  kk++;

            }
        }
        g<<nr1<<'\n'<<nr;
    }
    f.close(); g.close();
    return 0;
}
