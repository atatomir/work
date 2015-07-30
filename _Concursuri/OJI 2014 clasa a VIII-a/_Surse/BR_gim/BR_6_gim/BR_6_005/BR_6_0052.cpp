#include <fstream>
using namespace std;
long nr,n,i,x[100001];
int main()
{ifstream f("munte.in");
 ofstream g("munte.out");
 f>>n;
 for(i=1;i<=n;i++)
 f>>x[i];

 for(i=1;i<=n;i++)
 {if(x[i]>x[i+1])
 nr++;}

for(i=1;i<=n;i++)
{if(x[i]>x[i+1])
x[i+1]=0;
n--;}

g<<'\n'<<'\n'<<n;
 g<<nr;
 f.close();
 g.close();

    return 0;
}
