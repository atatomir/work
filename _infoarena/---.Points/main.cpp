#include <iostream>
#include <cstdio>

using namespace std;

long n,i;
long a,b;
long long cnt[2][2];
long long Ans;

long x[3],y[3];

void addAns(){
    long long val=1;
    val *= cnt[x[0]][y[0]];
    cnt[x[0]][y[0]]--;
    val *= cnt[x[1]][y[1]];
    cnt[x[1]][y[1]]--;
    val *= cnt[x[2]][y[2]];
    cnt[x[0]][y[0]]++;
    cnt[x[1]][y[1]]++;

    Ans += val;
}

int main()
{
    freopen("points.in","r",stdin);
    freopen("points.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&a,&b);
        cnt[a%2][b%2]++;
    }

    for(x[0]=0;x[0]<2;x[0]++)
    for(x[1]=0;x[1]<2;x[1]++)
    for(x[2]=0;x[2]<2;x[2]++)
    for(y[0]=0;y[0]<2;y[0]++)
    for(y[1]=0;y[1]<2;y[1]++)
    for(y[2]=0;y[2]<2;y[2]++){
        long tmp = x[0]*y[1]-x[1]*y[0] +
                   x[1]*y[2]-x[2]*y[1] +
                   x[2]*y[0]-x[0]*y[2] ;
        if(tmp%2 == 0)  addAns();
    }

    printf("%lld",Ans/6);

    return 0;
}
