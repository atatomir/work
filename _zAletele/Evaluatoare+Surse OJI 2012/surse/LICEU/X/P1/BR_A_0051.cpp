#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream f("calcule.in ");
    ofstream g("calcule.out");
   long int n;
   int k,i,j,V[3243],s=0,nr=0,nr2=0,a,aux;
   f>>n;
   f>>k;
  for(i=1;i<=n;i++)
    f>>V[i];
   if(V[i]%k==0)
    nr=nr+1;
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
  {

   s=s+V[i]+V[j];
    if(s%k==0)
    nr2=nr2+1;
    a=nr2+nr;
    }

    g<<a;
    f.close();
    g.close();


    return 0;
}
