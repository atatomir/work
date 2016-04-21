// Petru Trimbitas - 40 de puncte - O(M) doar elemente unice
#include <fstream>
#include <algorithm>

#define DN 1000005
using namespace std;

int n,x,v[DN],poz[DN], op;

int main() {
  ifstream f("undo2.in");
  ofstream g("undo2.out");
  f>>n;
  while(f>>op>>x) {
    if(op==1) {
      v[++n]=x;
      poz[x]=n;
    }
    else if(op==2) n-=x;
    else if(op==3) n+=x;
    else if(op==4) {
      g<<(poz[x]<=n && v[poz[x]]==x)<<'\n';
    }
  }
}
