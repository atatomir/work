#include <fstream>
using namespace std;
int main()
{int M2,M,N,K,D,i,j,z[101],t[101],y[101],x[101];
ifstream fin("betasah.in");
ofstream fout("betasah.out");
fin>>N>>K>>D;
for(i=1;i<=D;i++)
{
    fin>>x[i]>>y[i];
}
for(j=1;j<=K;j++)
{
    fin>>z[j]>>t[j];
}
M=N*(N+1)/2;
M2=N-K/2;
fout<<M2<<"\n"<<N+D+K;
return 0;
}