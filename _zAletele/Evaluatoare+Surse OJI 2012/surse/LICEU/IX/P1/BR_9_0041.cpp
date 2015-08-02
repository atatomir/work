#include<fstream>
using namespace std;
int main(){

 int n,d,k,i,j,x,y,z,t,a[100][100],m,p,max,b[100],q=0,w;

 ifstream f("betasah.in");
 ofstream g("betasah.out");

 f>>n>>d>>k;

 for(i=1;i<=n;i++)
  for(j=1;j<=n;j++){
   a[i][j]=1;
   a[n-i][n-j]=3;
  }

 for(i=1;i<=d;i++) {
  f>>x>>y;
  a[x][y]=2;
 }

 for(i=1;i<=k;i++) {
  f>>z>>t;
  a[z][t]=0;
 }

 for(i=1;i<=n;i++) {
  w=0;
  for(j=1;j<=n;j++) {
   if(a[i][j]==1)
    w++;
   b[++q]=w;
  }
 }

 for(i=1;i<=q;i++) {
  max=b[1];
  if(b[i]>max)
   max=b[i];
 }

 m=max;
 g<<m;

f.close();
g.close();
return 0;
}

