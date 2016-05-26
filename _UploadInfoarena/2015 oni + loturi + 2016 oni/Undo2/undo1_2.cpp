// Petru Trimbitas - MlogM - 100 puncte
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define DN 200005
#define LL long long
using namespace std;

int q,n,nn,v[DN];
vector<int> poz[DN];

void ups() {
  for(int i=max(nn,n); i>min(nn,n); --i)
    poz[v[i]].pop_back();
}

int main () {
  ifstream f("undo2.in");
  ofstream g("undo2.out");
  int op,x,m;
  f>>m;
  while(f>>op>>x) {
    if(op==1) {
      ups();
      v[++n]=x;
      nn=n;
      poz[x].push_back(n);
    }else if(op==2) {
      ups();
      nn=n;
      n-=x;
    }else if(op==3) n+=x;
    else if(op==4) {
      int p=upper_bound(poz[x].begin(), poz[x].end(),n)-poz[x].begin();
      g<<p<<'\n';
    }
  }
}
