#include <fstream>
using namespace std;
int main()
{int v,n,k,i,s,min=2000000001,a[47],x;
    ifstream f("triunghi.in");
    ofstream g("triunghi.out");
    f>>v>>n>>k;
    for(i=1;i<=n;i++)
      {
        f>>x;
        if(x<min)
          min=x;
      }
      s=min;
      g<<s<<" ";
    for(i=2;i<=k;i++)
       {
           s+=i;
           g<<s<<" ";
       }
    f.close();
    g.close();
    return 0;
}
