#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 1000

struct Square{
    long x,y,dim;
};
Square mp(long _x,long _y,long _dim){
    Square ans;
    ans.x=_x;ans.y=_y;ans.dim=_dim;
    return ans;
}

long n,k,i,j,x,y;
long sum[maxN+50][maxN+50];
vector<Square> ans;

void solve(long x,long y,long dim){
    long area = sum[x+dim-1][y+dim-1] - sum[x-1][y+dim-1] - sum[x+dim-1][y-1] + sum[x-1][y-1];
    if(area==0) return;
    if((area*k>=dim*dim)&&(area*k<4*dim*dim)){
        ans.push_back(mp(x,y,dim));
        return;
    }
    dim>>=1;
    solve(x,y,dim);
    solve(x+dim,y,dim);
    solve(x,y+dim,dim);
    solve(x+dim,y+dim,dim);
}

int main()
{
    freopen("patrate4.in","r",stdin);
    freopen("patrate4.out","w",stdout);

    scanf("%ld%ld",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%ld%ld",&x,&y);
        sum[x][y]=1;
    }
    for(i=1;i<=maxN+24;i++)
        for(j=1;j<=maxN+24;j++)
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];

    solve(1,1,maxN+24);
    printf("%ld\n",ans.size());
    for(vector<Square>::iterator it=ans.begin();it!=ans.end();it++){
        printf("%ld %ld %ld\n",(*it).x,(*it).y,(*it).dim);
    }

    return 0;
}
