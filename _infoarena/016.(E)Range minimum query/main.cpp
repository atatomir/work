#include <iostream>
#include <fstream>

using namespace std;

#define maxN 100005
#define maxRMQ 20

ifstream fin("rmq.in");
ofstream fout("rmq.out");

long n,m,i,j,l,lim,h,x,y,k,ans;
long rmq[maxRMQ][maxN];

long getLog(long x){
    long ans=0,aux=1;
    while(aux <= x) aux <<= 1,ans++;
    return ans-1;
}

int main()
{
    fin >> n >> m;
    for(i=1;i<=n;i++) fin >> rmq[0][i];
    l = getLog(n);

    for(i=1;i<=l;i++){
        lim = n - (1 << i)+1;
        h = 1 << (i-1);
        for(j=1;j<=lim;j++) rmq[i][j] = min(rmq[i-1][j],rmq[i-1][j+h]);
    }

    for(i=1;i<=m;i++){
        fin >> x >> y;
        k = getLog(y-x+1); h = 1 << k;
        ans = min(rmq[k][x],rmq[k][y-h+1]);
        fout << ans << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
