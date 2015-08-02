#include <iostream>
#include <fstream>

using namespace std;
int n , st[100], a[100], b[100], viz1[100], viz2[100], v1[100] , v2[100];
int mina=100000;
ifstream f1("biperm.in");
ofstream f2("biperm.out");
int gata ()
{    int i, d=0;
     int gasit=1;
     for (i=1; i<=n; i++) if (viz1[i]!=1) gasit=0;
     for (i=1; i<=n; i++) if (viz2[i]!=1) gasit=0;
     if (gasit==0) return 0;
     for (i=1; i<=n; i++) if (st[i]==2) d++;
     if (d<mina )
     {
         mina=d;
         for (i=1; i<=n; i++) { v1[i]=a[i]; v2[i]=b[i];}
     }
     return 1;
}
int main()
{  int k=1;
   int i, aux;
   f1 >>n;
   for (i=1; i<=n; i++) { f1>>a[i]; viz1[a[i]]++;}
   for (i=1; i<=n; i++) {f1>>b[i]; viz2[b[i]]++;}
   int c=0;

   while (k>0)
   {
    if (k==n+1) { if (gata()) {c++; } k--; }
    else  if(st[k]<2) {st[k]++; if (st[k]==2 ) { viz1[a[k]]--; viz2[b[k]]--; viz1[b[k]]++; viz2[a[k]]++; aux=a[k]; a[k]=b[k]; b[k]=aux; }  k++; }
    else {viz1[a[k]]--; viz2[b[k]]--; viz1[b[k]]++; viz2[a[k]]++; aux=a[k]; a[k]=b[k]; b[k]=aux; st[k]=0; k--; }
   }
    f2 <<c<<" "<< mina;
    f2 <<endl;
    for (i=1; i<=n; i++ ) f2<<v1[i] << " ";
    f2<<endl;
    for (i=1; i<=n; i++ ) f2<<v2[i]<< " ";
    return 0;
}
