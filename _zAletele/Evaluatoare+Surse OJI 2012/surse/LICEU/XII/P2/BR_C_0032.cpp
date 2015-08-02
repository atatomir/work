#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
ifstream f1("subsecvente.in");
ofstream f2("subsecvente.out");
char s[4000], a[400][400];
int n, m, maxa=0, p, k, v[400] ,gasit, ok ,z , t;
int main()
{   int i, j, mina=100000, c;
    f1>>n;
    for (i=1; i<=n; i++)
    {
        f1>>s;
        m=strlen(s);
        for (j=1; j<=m; j++)  {a[i][j]=s[j-1]; v[i]=m; }
        if (m<mina) {mina=m; c=i;}
        if (maxa<m) maxa=m;
    }
    m=maxa;
    p=mina;

    for (k=p; k>=1; k--)
    {  gasit=1;

      for (i=1; i<=n; i++ )
      { t=0;
        for (j=0; j<=v[i]-k; j++)
        {   ok=1;
            for (z=1+j; z<=k+j; z++) if (a[c][z-j]!=a[i][z]) ok=0;
            if (ok==1) t=1;
        }
        if (t==0) gasit=0;
      }
       if (gasit==1) {f2<<k; return 0;}
    }
    return 0;
}
