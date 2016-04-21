// Petru Trimbitas - N*M*log(N*M) - 100 puncte
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#define DN 1005
#define x first
#define y second
using namespace std;

typedef pair<int,int> per;

int n,m,lgm,lm[DN][DN],sz,q,w;
char mt[DN][DN];
vector<per> pt[DN];
per el[DN*DN];

int main() {
  ifstream f("tort3.in");
  ofstream g("tort3.out");
  f>>n>>m;
  for(int i=1; i<=n; ++i) f>>(mt[i]+1);
  for(int i=1; i<=n; ++i) {
    for(int j=1; j<=m; ++j) {
      lm[i][j]=1;
      if(mt[i][j]==mt[i-1][j] && mt[i][j]==mt[i][j-1] && mt[i][j]==mt[i-1][j-1]) 
        lm[i][j]=max(lm[i][j],1+min(lm[i-1][j-1],min(lm[i-1][j],lm[i][j-1])));
      pt[lm[i][j]].push_back(make_pair(i,j));
      lgm=max(lm[i][j],lgm);
    }
  }
  for(int lgc=lgm; lgc>0; --lgc) {
    sort(pt[lgc].begin(), pt[lgc].end());
    for(auto j:pt[lgc]) {
      int x=j.x,y=j.y;
      if(lm[x][y]<lgc) continue;
      g<<lgc<<' '<<x<<' '<<y<<'\n';
      for(int i=-lgc+1; i<lgc; ++i) for(int j=-lgc+1; j<lgc; ++j) {
        int l=x+i,c=y+j;
        if(l>n || c>m) continue;
        if(i<=0 && j<=0){
          lm[l][c]=0;
          mt[l][c]='-';
        } else if(mt[l][c]!='-'){
          lm[l][c]=1;
          if(mt[l][c]==mt[l-1][c] && mt[l][c]==mt[l][c-1] && mt[l][c]==mt[l-1][c-1]) 
            lm[l][c]=max(lm[l][c],1+min(lm[l-1][c-1],min(lm[l-1][c],lm[l][c-1])));
          pt[lm[l][c]].push_back(make_pair(l,c));
        }
      }
    }
  }
}
