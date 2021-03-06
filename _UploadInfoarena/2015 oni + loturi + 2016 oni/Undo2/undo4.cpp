// Petru Trimbitas - 20 de puncte - O(M^2)
#include <iostream>
#include <fstream>
#define DN 1000005
using namespace std;

int n,v[DN];

int main() {
  ifstream f("undo2.in");
  ofstream g("undo2.out");
  int n,op,x;
  f>>n;
  while(f>>op>>x) {
    if(op==1) v[++n]=x;
    else if(op==2) n-=x;
    else if(op==3) n+=x;
    else if(op==4) {
      int p=0;
      for(int i=1; i<=n; ++i) p+=(v[i]==x);
      g<<p<<'\n';
    }
  }
}
