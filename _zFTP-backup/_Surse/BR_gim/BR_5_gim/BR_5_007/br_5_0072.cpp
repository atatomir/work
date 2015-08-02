#include <fstream>

using namespace std;

int main()
{ int N,X,K,P,M,C,A,min,n;
    ifstream f("piramide.in");
   ofstream g("piramide.out");
   min=3;
f>>N>>X;
if(9<X)if(X=10,11,12,13,14,15,16,17,18,19<20)
      {g<<3;}
if(X=1,2,3<4)
      {g<<1;}
if(3<X)if(X=4,5,6,7,8,9<10)
      {g<<2;}
      g<<endl;
      f>>n;
   if(n*n+n<N)if(N<n*n+2*n)
   g<<n;
    return 0;
}
