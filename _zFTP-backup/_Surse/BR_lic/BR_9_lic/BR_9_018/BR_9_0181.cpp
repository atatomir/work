#include <fstream>

using namespace std;

int main()
{
    int p,n,k,i,j,c,e,l,h,q,w;
    ifstream f("cool.in");
    ofstream g("cool.out");
    f>>p;
    f>>n>>k;
    int a[n],b[n];
    for(i=1;i<=n;i++)
        f>>a[i];
    if (p==1) {
                for(i=1;i<k;i++)
                    for(j=i+1;j<=k;j++)
                        if(a[i]>a[j]) {c=a[i];
                                       a[i]=a[j];
                                       a[j]=c;}
                c=1;
                for(i=1;i<k && c!=0;i++)
                        if(a[i]!=a[i+1]-1) c=0;
                if(c==1) g<<a[k];
                        else
                         {   q=0;
                             for(i=1;i<=k;i++)
                                {   c=1;
                                    for(j=1;j<k && c==1;j++)
                                              if(a[i]==a[j]) c=0;
                                    if(c==1) q++;}
                             if(a[k]!=a[k-1]) q++;
                             g<<q;
                         }
              }
              else
              {
                  c=0;
                  for(i=n;c!=1;i--)
                      {
                         e=n-i+1;
                         for(l=1;l<=e;l++)
                            for(j=l;j<=i;j++)
                               b[j]=a[i];
                            for(j=1;j<k;j++)
                                for(w=i+1;w<=k;w++)
                                    if(b[j]>b[w]) {q=b[j];
                                                   b[j]=b[w];
                                                   b[w]=q;}
                            h=1;
                            for(q=1;q<k && h!=0;i++)
                                      if(a[i]!=a[i+1]-1) h=0;
                            if(h==1) c=1;
                      }
                  f>>e;
                  for(i=1;i<=n-e;i++)
                     {   w=1;
                         for(j=i;j<=i+e;j++)
                             {
                                 b[w]=a[j];
                                 w++;
                             }
                     }
              }
    f.close();g.close();
    return 0;
}
