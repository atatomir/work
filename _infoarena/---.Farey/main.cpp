#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 40111

struct fr{
    long up,down;
};
bool cmp(const fr& a,const fr& b){
    return a.up*b.down < a.down*b.up;
}

long n,k,act,x,cont,i;
long cnt[maxN];
fr tmp[maxN];

long make_cnt(long up){
    long i,j,sum=0;
    for(i=1;i<=n;i++) cnt[i] = (i*up)/n;
    for(i=2;i<=n;i++){
        for(j=i*2;j<=n;j+=i)
            cnt[j]-=cnt[i];

        sum += cnt[i];
    }
    return sum;
}


long getAct(){
    long i=1,j=n-1,m;
    while(i<=j){
        m=(i+j)>>1;
        if(make_cnt(m)<=k)
            i=m+1;
        else
            j=m-1;
    }
    return j;

}

bool ired(long id){
    long a=tmp[id].up,b=tmp[id].down,tt;
    while(b){
        a %= b;
        tt = a;a = b;b = tt;
    }
    if(a==1) return true;
    return false;
}

int main()
{
    freopen("farey.in","r",stdin);
    freopen("farey.out","w",stdout);

    scanf("%ld %ld",&n,&k);

    act = getAct();
    for(i=2;i<=n;i++){
        x = (i*act+n-1)/n;
        tmp[++cont].up = x;
        tmp[cont].down = i;
    }

    long tcont=cont;cont=0;
    for(i=1;i<=tcont;i++){
        if(ired(i)) tmp[++cont] = tmp[i];
    }
    sort(tmp+1,tmp+cont+1,cmp);

    k = k- make_cnt(act) + 1;
    printf("%ld %ld",tmp[k].up,tmp[k].down);

    return 0;
}
