#include <fstream>
#include <iostream>

using namespace std;
int b,k,n,p1,p2,s1,s2,b1,j,i;
long long s, v1[200000000];
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");

int main()
{f>>n;
f>>b;
f>>k;
f>>s1;
f>>p1;

s=b+n-1;
g<<s<<"\n";
for ( i=1;i<=s1;i++)
    {for(j=1;i<=n;j++)
        if(p1)
        {
            v1[1]=b-1;
            b--;
            v1[i+1]++;
        }
    }
g<<v1[1]<<" ";
g<<v1[i+1]<<"\n";

f.close();
g.close();
return 0;
}
