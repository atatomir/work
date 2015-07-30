#include <iostream>
#include <cstdio>

using namespace std;

long n,i,x,y,xx,yy;
long long ans;

long Cf(long x){
    long ans=0;
    while(x){
        ans += x%10;
        x /=10;
    }
    return ans;
}
long long sum(long x,long y){
    long i,left,right;
    long long ans=0,act=0;

    for(i=1;i<=y;i++) act+=Cf(i);
    ans = act; left = 1; right = y;

    for(i=2;i<=x;i++){
        left--; if(left==0) left=n;
        act += Cf(left) - Cf(right);
        right--; if(right==0) right = n;

        ans += act;
    }
    return ans;
}

int main()
{
    freopen("piata.in","r",stdin);
    freopen("piata.out","w",stdout);

    scanf("%ld%ld%ld%ld%ld",&n,&x,&y,&xx,&yy);
    ans = sum(xx,yy)-sum(x-1,yy)-sum(xx,y-1)+sum(x-1,y-1);
    printf("%lld",ans);

    return 0;
}
