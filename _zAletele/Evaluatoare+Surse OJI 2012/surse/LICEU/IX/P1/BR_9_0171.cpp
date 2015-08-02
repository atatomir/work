#include<iostream>
#include<fstream>
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int D,N,K,i,j,v[1001][1001],a,b,k;
int main()
{
    int max=0;
    f>>D>>N>>K;
    for(i=1;i<=N;i++)
        {
            f>>a>>b;
            v[a][b]=2;
            }
            for(j=1;j<=N;j++)
        {
            if((v[i][j]=0) || (v[i][j]=1))
            k++;
        }
        if(k>max)
            max=k;
}
    g<<max<<'/n'

f.close();
g.close();
return 0;
}
