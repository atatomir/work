#include<fstream>
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int D,N,K,i,j,a,b,k,v[1001][1001],s,z;
int main()
{
    int max=0;
    f>>N>>D>>K;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
            v[i][j]=5;
    }
    for(i=1;i<=N;i++)
    {
        s++;
        for(j=1;j<=s;j++)
            v[i][j]=0;
    }
    for(i=1;i<=D;i++)
    {
        f>>a>>b;
        v[a][b]=1;
    }
    for(j=D+1;j<=D+K;j++)
    {
        f>>a>>b;
        v[a][b]=2;
    }
    for(i=1;i<=N;i++)
    {
        k=0;
        for(j=1;j<=N;j++)
        {
            if( (v[i][j]==0) || (v[i][j]==1) )
                k++;
        }
        if(k>max)
            max=k;
    }
    g<<max<<'\n';
f.close();
g.close();
return 0;
}
