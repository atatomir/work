//Petru Trimbitas - N^2*M^2 - 30 puncte
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#define DN 1005
#define x first
#define y second
using namespace std;

int n,m,lm[DN][DN];
char mt[DN][DN];

int main() {
  ifstream f("tort3.in");
  ofstream g("tort3.out");
  f>>n>>m;
  for(int i=1; i<=n; ++i) f>>(mt[i]+1);
  int lgm=-1,x,y;
  while(lgm) {
    lgm=0;
    for(int i=1; i<=n; ++i) {
      for(int j=1; j<=m; ++j) {
        if(mt[i][j]!='-') {
          lm[i][j]=1;
          if(mt[i][j]==mt[i-1][j] && mt[i][j]==mt[i][j-1] && mt[i][j]==mt[i-1][j-1]) 
            lm[i][j]=max(lm[i][j],1+min(lm[i-1][j-1],min(lm[i-1][j],lm[i][j-1])));
          if(lm[i][j]>lgm) {
            lgm=lm[i][j];
            x=i; y=j;
          }
        }else lm[i][j]=0;
      }
    }
    if(lgm) g<<lgm<<' '<<x<<' '<<y<<'\n';
    for(int i=x-lgm+1; i<=x; ++i) for(int j=y-lgm+1; j<=y; ++j) mt[i][j]='-';
  }
}
