#include <iostream>
#include<fstream>
#include<string.h>
using namespace std;

int main()
{int n,k,t,nr=0,i,j;
char *p,s[245],s1[256];
ifstream f("calcule.in");
ofstream g("calcule.out");
f>>n>>k;
f.get();
f.get(s,256);
cout<<s<<'\n';
p=strtok(s," ");
t=0;
g<<"12 .\n";
cout<<"Proba "<<s+strlen(p);
while(p)
{  j=*p-'0';
   t=t+j;
   cout<<"t="<<t<<' ';
    if(t%k==0)
        nr++;
    p=strtok(s+1," NULL");

}
g<<nr;
f.close();
g.close();
    return 0;
}
