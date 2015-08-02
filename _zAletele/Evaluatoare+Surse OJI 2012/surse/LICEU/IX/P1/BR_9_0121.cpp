#include <iostream>
#include <fstream>
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int main()
{int spt[50][50],d[50][50],p[50][50];
unsigned N,D,K,j,x,y,z,t,i,P=0,q,w;
f>>N>>D>>K;
{for(j=1;j<=(N*(N+1))/2;j++)
    P++;}
for(i=1;i<=(N*(N+1))/2;i++)
for(j=1;j<=(N*(N+1))/2;j++)
for(q=1;q<=D;q++)
f>>x>>y;
if(spt[i][j]==d[x][y])
P--;
g<<"\n"<<P;
return 0;
}
