#include <fstream>
using namespace std;
int w[46],n,g[46];

void calc(int k){
int a=w[1]+1,h=2,i,j;
while (h<k){int e=0;
for(i=1;i<=h-1;i++)
for(j=i+1;j<=h;j++){

if(w[i]+w[j]>a)e=1;
}

if(e==0){w[++h]=a;}
a++;
}
}

void va(int k,int m){
    int i;w[1]=m;w[2]=m;
calc (k);
ofstream l("triunghi.out");
for(i=1;i<=k;i++)
l<<w[i]<<" ";
}

int min(int n){
int m=g[1],i;
for (i=1;i<=n;i++) if(m>g[i])m=g[i];
return m;
}
int main()
{ int v,k,i;
  ifstream f("triunghi.in");
  f>>v>>n>>k;
  for (i=1;i<=n;i++)f>>g[i];

  if(v==1){
  va(k,min(n));
  }
  else if(v==2){

  }
    return 0;
}
