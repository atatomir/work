#include <fstream>
using namespace std;
int main()
{ ifstream f("cool.in");
  ofstream g("cool.out");
   int p,n,k,i,min=1001,min2,ok=0,j=1,ci=0,cf=0,S=0;
   bool verificare = true ;
   f >> p >> n >> k ;
   int a[n] ;
 if ( p == 1 )
 { for (i=1;i<=n;i++)
   f >> a[i] ;
   for (i=1;i<=k;i++)
   if (a[i] < min) min = a[i] ;
min2 = min ;
   for (i=1;i<=k;i++)
    {do
    {if (a[i] == a[j+1])  ok = 1 ;
     j++;}while (j<=k-1);
    if (j==k-1) { i++ ; j = 1; }}
    if (ok == 1)  {  verificare = false ; }
ok = 0 ;
if (verificare == true)
 { for (i=1;i<=k;i++)
    for (j=1;j<=k;j++)
      {  if ( a[j] == min2 +1 ) ok++ ;
         if (j==k) min2++ ; }
min = -1 ;
   if (ok==k-1)
   { for (i=1;i<=k;i++)
       if (a[i]>min) min = a[i] ; }
   g << min;
 }
 S = k ;
ci = k+1 ;
 j = 1 ;
      if (verificare == false )
      {for (i=1;i<=k;i++)
    {ci --; cf = ci ;
        do
    {if (a[i] != a[j+1])  cf-- ;
     j++;}while (j<=k-1);
    if (j==k-1) { S = S - cf ; i++ ; j = 1; }
    }
       g<<S ;}
 }
 if (p == 2 )
 {  int v[n] ;ok = 1;
      for (i=1;i<=n;i++)
   f >> a[i] ;
   for (i=1;i<=n;i++)
   if (a[i] < min) min = a[i] ;
min2 = min ;
      for (i=1;i<=n;i++)
    for (j=1;j<=n;j++)
      {  if ( a[j] == min2 +1 ) ok++ ;
         if (j==n) { min2++ ;v[i] = ok ;ok = 1 ;} }
ok = 0 ;
for (i=1;i<=n;i++)
v[i] = v[i] + 2 ;
min = -1 ;
for(i=1;i<=n;i++)
if (v[i] > min ) min = v[i] ;
for (i=1;i<=n;i++)
if (v[i]==min) v[i] = -1 ;
min = -1;
for(i=1;i<=n;i++)
if (v[i]>min) min = v[i] ;
for(i=1;i<=n;i++)
if (v[i]== min) ok++ ;
 g<<min<<'\n';
 g<<ok;
 }
   f.close();
   g.close();
    return 0;
}
