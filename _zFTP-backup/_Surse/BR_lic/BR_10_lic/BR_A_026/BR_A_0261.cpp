#include <fstream>
#include <iostream>
#include<string.h>
using namespace std;


int n,m;
char a[400][400];int x[400][400];
void v1(){
    int max=0,i,j,t=1;

x[0][0]=1;
for(i=0;i<=m;i++)
for(j=0;j<=n;j++){
if(a[i][j]==a[i][++j])x[i][++j]=x[i][j];
else if(a[i][j]!=a[i][++j])x[i][++j]=t+1;
if(a[i][j]==a[++i][j])x[++i][j]=x[i][j];
else if(a[i][j]!=a[++i][j])x[++i][j]=t+1;
}
for(i=0;i<=m;i++)
for(j=0;j<=n;j++){
    cout<<x[i][j];}

ofstream g("ferma.out");
g<<max;}
int main(){
     int v,i,j;
  ifstream f("ferma.in");
  f>>v>>m>>n;
  for(i=0;i<=m;i++)
f>>a[i];



  if(v==1){v1();}
  else if(v==2){

  }
    return 0;
}
