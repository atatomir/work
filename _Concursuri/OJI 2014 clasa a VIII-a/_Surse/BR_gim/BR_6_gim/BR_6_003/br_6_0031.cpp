#include <fstream>

using namespace std;
long i,c,a,n,N,v[1001],w[1001],x,z[1001],max1,max2,max3,max4;

int main()
{   fstream f("imprimanta.in");
    ofstream g("imprimanta.out");
    f>>N;
{for(i=1;i<=n;i++)
f   >>v[i];
for(c=0;c<=9;c++)
    f>>w[c];
for(x=5;x<=13;x++)
    f>>z[x];
for(N=1;N<=n;N++)

    max1=0;
    max2=0;
for(c=0;c<=9;c++)
    max2=max1;

    max3=0;
    max4=0;
for(x=5;x<=13;x++)
    max3=max4;
    }



    g<<N<<" ";
// char


    f.close();
    g.close();

return 0;
    }
