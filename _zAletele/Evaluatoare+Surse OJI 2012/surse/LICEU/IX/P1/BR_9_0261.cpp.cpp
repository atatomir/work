#include <iostream>
#include<fstream>
#define Nmax 1001
#define Dmax 101
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int main()
{
    int M,K,i,j,v[Nmax][Nmax],c[Dmax],N,D,nr,d;
    unsigned P;
f>>N>>D>>K;
for(i=1;i<=Nmax;i++)
for(j=1;j<=Nmax;j++)
{
    f>>v[N][N];
    v[N][N]=(N*(N+1))/2;
}
for(i=1;i<=6;i++)
  if(i>K)
     M=K+1;
else
    M=K-1;
  g<<M<<"\n";

nr=((N*(N+1))/2)-K;
for(d=1;d<=D;d++)
    {c[d]=d;P=nr-c[d];}
    g<<P;


f.close();
    g.close();

}
