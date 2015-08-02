#include <iostream>
#include<fstream>
using namespace std;
int main ()
{ int n,i,h[1000],hmax,nrcub,br[1000],bc[1000],hr,hc,nr;
float min;
 ifstream f("cladiri.in");
 ofstream g("cladiri.out");
 f>>n;
 for(i=1;i<=n;i++)
    {cin>>h[i];
    hmax=0;
    if(h[i]>hmax)
    h[i]=hmax;
    hmax=1;
    if(hmax>1)
    hmax++;}
 g<<"inaltimea celui mai inalt turn este"<<hmax<<endl;
for(i=1;i<=n;i++)
for(i=n;i<=1;i--)
    {if(bc[i]==br[i])
    nr=1;}
g<<"numarul de bilete lipite de amandoi copii care sunt identice"<<nr<<endl;
for(i=1;i<=n;i++)
    {while(hc=hr+nrcub)
    if(nrcub<min)
    nrcub=min;}
 g<<"cel mai mic numar de cuburi este"<<min<<endl;
 f.close();
g.close();
return 0;
}
