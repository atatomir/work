#include <fstream>
using namespace std;
int main()
{
int v,k=0,n,w[50],i,s=0,e=0;
ifstream f("arc.in");
ofstream g("arc.out");
f>>v>>n;
for(i=1;i<=n;i++) f>>w[i];
for(i=1;i<=n;i++) if(w[i]==w[i+1]) k++;
if(k>=3) for(i=1;i<=n;i++){ if(w[i]==w[i+1]&&w[i]==w[i-1]) {w[i]=0;s++;}
else e++;}
for(i=1;i<=n;i++) w[i]=w[i+1];
if(v==2)
{g<< e<<'\n';
for(i=1;i<=n;i++) if(i!=0) g<<w[i]<<'\n';}
else g<<s++;
f.close();
g.close();
return 0;
}
