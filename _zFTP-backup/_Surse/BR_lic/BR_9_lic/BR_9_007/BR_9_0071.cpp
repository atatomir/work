#include <iostream>
#include <fstream>

using namespace std;

int main()
{   ifstream f("cool.in");
    ofstream g("cool.out");
    int n,k,p,i,v,q,nr,max,j;
    f>>p;
    f>>n>>k;
    long a[n],b[n];
    for (i=1; i<=n; i++) f>>a[i];
    if (p==1)
       {
           for (i=1; i<=k; i++)
              b[i]=a[i];
           for (i=1; i<=k; i++)
                  if (b[i]>b[i+1])
                    {
                        v=b[i];
                        b[i]=b[i+1];
                        b[i+1]=v;
                    }
             q=0;
            for (i=k; i>=1; i--)
               if (b[i]-b[i-1]!=1) q++;
            if (q==0)
              {
                  max=b[1];
                  for (i=1; i<=k; i++) if (max<b[i]) max=b[i];
                  g<<max;
              } nr=0;
              else for (i=1; i<=k; i++)
                     { v=0; q=b[i];
                        for (j=1; j<=k; j++)
                          if (q==b[i]) v++;
                        if (v==0) nr++;
                     }
                g<<nr;
       }
    if (p==2)
      {
          for (i=1; i<=n; i++)
            {for (j=1; j<=i; j++)
              b[j]=a[j];
             for (v=1; v<=i; v++)
                if (b[i]>b[i+1])
                    {
                        q=b[i];
                        b[i]=b[i+1];
                        b[i+1]=q;
                    } nr=0;
             for (v=1; v<=i; v++)
               if (b[v+1]-b[v]!=0) nr++;
             if (nr==0) max=i;
            }
         for (i=1; i<=n; i++)
            {for (j=i; j<=max; j++)
                b[i]=a[i];
             for (j=1; j<=max; j++)
                if (b[j]>b[j+1])
                    {
                        q=b[j];
                        b[j]=b[j+1];
                        b[j+1]=q;
                    } nr=0; q=0;
             for (j=1; j<=max; j++)
               if (b[j+1]-b[j]!=0) nr++;
             if (nr==0) q++;
            }
            g<<q;
      }
 f.close(); g.close();
 return 0;
}
