#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 30011
#define limInf 0

struct elem{
    long val,pos;
};
bool cmp(const elem& a,const elem& b){
    return a.val<b.val;
}

long n,lim,sum,act,i,j,m;
elem a[maxN];
long ans[maxN];

bool checkLess(long d){
    long act=sum,last=limInf,i;
    for(i=1;i<=n && act;i++){
        long decr = min(d,a[i].val-last-1); decr=min(decr,act);
        act -= decr; last = a[i].val-decr;
    }
    if(act) return false;
    return true;
}
void modLess(long d){
    long act=sum,last=limInf,i;
    for(i=1;i<=n && act;i++){
        long decr = min(d,a[i].val-last-1); decr=min(decr,act);
        act -= decr; last = a[i].val-decr;
        a[i].val -= decr;
    }
}

bool checkMore(long d){
    long act=sum,last=lim+1,i;
    for(i=n;i && act;i--){
        long incr = min(d,last-a[i].val-1); incr=min(incr,act);
        act -= incr; last = a[i].val+incr;
    }
    if(act) return false;
    return true;
}
void modMore(long d){
    long act=sum,last=lim+1,i;
    for(i=n;i && act;i--){
        long incr = min(d,last-a[i].val-1); incr=min(incr,act);
        act -= incr; last = a[i].val+incr;
        a[i].val += incr;
    }
}

int main()
{
    freopen("abc.in","r",stdin);
    freopen("abc.out","w",stdout);

    scanf("%ld%ld%ld",&n,&lim,&sum);
    for(i=1;i<=n;i++) {
        scanf("%ld%",&a[i].val);
        a[i].pos = i; act+=a[i].val;
    }
    sort(a+1,a+n+1,cmp); a[n+1].val = lim+1;

    sum = sum-act;
    if(sum<0){
        sum = -sum;
        i=0;j=65600;
        while(i<=j){
            m = (i+j)>>1;
            if(checkLess(m))
                j = m-1;
            else
                i = m+1;
        }

        modLess(i);
    } else {
        i=0;j=65600;
        while(i<=j){
            m=(i+j)>>1;
            if(checkMore(m))
                j = m-1;
            else
                i = m+1;
        }
        modMore(i);
    }

    for(i=1;i<=n;i++) ans[a[i].pos] = a[i].val;
    for(i=1;i<=n;i++) printf("%ld ",ans[i]);

    return 0;
}
