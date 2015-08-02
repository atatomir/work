#include <iostream>
#include <fstream>

using namespace std;
unsigned long int putere(unsigned int n)
{unsigned int aux;
unsigned long int q;
aux=n-1;q=1;
while(aux!=0)
{q=q*2;
aux--;
}
return q;
}

int main()
{unsigned int n,p,i,m,k,s,v[20],nr;

ifstream f("fractii2.in.txt");
f>>p;
f>>n;

if(p==1) // Punctul a);

{
ofstream g("fractii2.out.txt");
for(i=1;i<=n;i++)
g<<"2 ";
}


else    // Punctul b);

{

for(i=1;i<=n;i++)
v[i]=2;
nr=1;m=n;k=0;
do
{s=0;
if(v[m]!=putere(n))v[m]=v[m]*2;
else
{m=m-1;
v[m]=v[m]*2;
}
for(i=1;i<=n;i++)
{if(v[i]!=v[m])
{k=v[m]/v[i];
s=k+s;
}
else s++;
}
if(s==putere(m))nr++;
}while(v[1]!=putere(n));
ofstream g("fractii2.out.txt");
g<<nr;
}
return 0;
}
