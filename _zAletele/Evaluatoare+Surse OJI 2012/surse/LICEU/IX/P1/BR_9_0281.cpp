#include <iostream>
#include <fstream>
using namespace std;
int i,j,s,s2,M;
int main()
{ int N,D,K,y[1000],x[1000],t[1000],z[1000],a;
ifstream f("betasah.in");
ofstream g("betasah.out");
   f>>N>>D>>K;
  for (i=1;i<=D;i++){i++;f>>y[i]>>x[i];}
  for (i=1;i<=K;i++){j++;f>>t[j]>>z[j];}
// nr max de patrate albe
 for (a=1;a<=N;a++){ s=0;
    for (i=1;i<=D;i++)  if(a==y[i])s++;
    for (j=1;j<=K;j++)  if(a==t[j])s++;
     s2=a-s; if (M<=s2) M=s2;}
     g<<M<<"\n";


f.close();
g.close();
return 0;
}
