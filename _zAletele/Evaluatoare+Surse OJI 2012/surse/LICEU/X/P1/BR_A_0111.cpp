#include <fstream>
using namespace std;

ifstream f("calcule.in");
ofstream g("calcule.out");

int i,j,n,k,a[100004],b[100004],ok,ok2,nrs,sc,s,nrsec,x;

int main()
{
f>>n;
for (i=1;i<=n;i++) b[i]=1;
f>>k;
f>>a[1];
nrs=1;
for (i=2;i<=n;i++)
{
    f>>a[i];
    ok=0;
    sc=1;
    while (ok==0)
    {
        ok2=0;
        j=i-1;
        while (ok2==0)
            {
                if (b[j]==sc) ok2=1;
                    else j--;
            }
        if (a[i]>a[j]) { b[i]=sc; ok=1; }
            else {
            sc++;
        if (sc>nrs) {ok=1; b[i]=sc; nrs++;}
                  }
    }
}
g<<nrs<<endl;
b[1]=a[1]%k;
nrsec=0;
for (i=2;i<=n;i++) { b[i]=(a[i]%k+b[i-1])%k; if (b[i]==0) nrsec++; }
for (j=2;j<=n;j++)
    {
        for (i=j;i<=n;i++) {b[i]=b[i]-b[j-1]; if (b[i]==0) nrsec++; }
    }


g<<nrsec;
f.close();
g.close();
return 0;
}
