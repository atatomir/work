#include <fstream>

using namespace std;

int main()
{
    int nr,p,k,w,n,r,t,q,e,i,s,u,j;
    float d;
    ifstream f("pseudobil.in");
    ofstream g("pseudobil.out");
    f>>p;
    f>>n>>k>>d;
    int a[n][n];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            a[i][j]=0;
    for(i=1;i<=k;i++)
       {
           f>>r>>t;
           a[r][t]=1;
       }
    f>>q;
    w=2*q;
    int b[w];
    for(i=1;i<=q;i++)
       {f>>b[i]>>b[i+1];i++;}
    if(p==1){
              d=d-1;
              e=d;
              w=0;
              while(e!=1)
                 {
                     e=e-2;
                     w++;
                 }
              nr=1;
              e=2;
              for(i=1;i<=w;i++)
                  {
                      nr=nr+2;
                      e=e+2*nr;
                  }
              e=e-d;
              g<<e;
            }
            else
            {
               d=d+1;
               e=d/2+0.5;
               r=0;
               for(u=1;u<=2*q;u++)
                   {
                       s=0;
                       for(i=b[u];i<=d;i++)
                            {
                               if(r<=e) r++;
                                        else
                                        r--;
                               for(j=b[u+1]-r;j<=i+r;j++)
                                      if(a[i][j]==1) s++;
                            }
                       u++;
                       g<<s<<'\n';
                   }
            }
    f.close();g.close();
    return 0;
}
