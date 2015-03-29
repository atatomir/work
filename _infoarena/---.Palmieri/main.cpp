#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 250011

struct Palm{
    long x,y;
};
bool cmp(const Palm& a,const Palm& b){
    return a.x < b.x;
}

long n,a,i,h,l,cnt;
Palm p[maxN];

int main()
{
    freopen("palmieri.in","r",stdin);
    freopen("palmieri.out","w",stdout);

    scanf("%ld %ld",&n,&a);
    for(i=1;i<=n;i++) scanf("%ld%ld",&p[i].x,&p[i].y);
    sort(p+1,p+n+1,cmp);

    cnt=0;
    for(i=1;i<=n;i++){
        h = p[i].y; l = 0; cnt++;
        while(i<n && (max(h,p[i+1].y)*(l+p[i+1].x-p[i].x) <=a)) {
            h = max(h,p[i+1].y);
            l += p[i+1].x-p[i].x;
            i++;
        }
    }

    printf("%ld",cnt);

    return 0;
}
