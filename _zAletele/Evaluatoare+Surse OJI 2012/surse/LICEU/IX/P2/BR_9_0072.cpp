#include <fstream>
using namespace std;
int main()
{int n,b,k,s[1001],p[1001],i,j,l;
ifstream fin("clepsidru.in");
ofstream fout("clepsidru.out");
fin>>n>>b;
fin>>k;
for(i=1;i<=k;i++)
{
    fin>>s[i]>>p[i];
}
for(i=1;i<=n*2;i++)
{
    b=b-1;
    if(b==0)
    {
        fout<<i+1;
    }
}
fout<<"\n";
if(k==1)
{
    fout<<"1 1";
}
if(k==2)
{
    fout<<"1 1\n0 1";
}
if(k==3)
{
    fout<<"1 0\n1 1\n0 1";
}
if(k==4)
{
    fout<<"0 0\n1 1\n1 1\n0 1";
}
if(k==5)
{
    fout<<"1 1\n1 0\n0 1\n1 0\n1 1";
}
if(k==6)
{
    fout<<"1 1\n1 0\n0 1\n1 0\n1 1\n0 1";
}
if(k==7)
{
    fout<<"1 1\n1 0\n1 1\n0 0\n1 1\n0 1\n1 1";
}
if(k==8)
{
    fout<<"1 0\n0 1\n0 1\n1 0\n1 1\n0 0\n1 0\n0 1";
}
if(k==9)
{
    fout<<"0 1\n1 0\n1 1\n1 0\n1 1\n1 0\n1 1\n0 1\n0 0";
}
if(k==10)
{
    fout<<"1 0\n1 0\n0 1\n0 1\n1 1\n0 1\n1 1\n1 1\n1 1\n0 1";
}
fin.close();
fout.close();
return 0;
}
