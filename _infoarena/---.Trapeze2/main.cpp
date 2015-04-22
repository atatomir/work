#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

inline long long abss(long x){
    if(x<0) return -x;
    return x;
}

#define x1 xx1
#define x2 xx2
#define y1 yy1
#define y2 yy2

long long i,x,drept,cnt;
long long x1,d1,n1;
long long x2,d2,n2;
long long ans = 0;

pair<long long,long> isKey(long long val){
    static long long h;
    //! Case 1
        h = val - x1;
        if(h%d1==0){
            h /= d1; h++;
            if(h>n1 || h<=0) return make_pair(-1,-1);
            return make_pair(val,min(h-1,n1-h));
        }
    //! Case 2
        h = val - x1 - (d1>>1);
        if(h%d1==0){
            h /= d1; h++;
            if(h>=n1 || h<=0) return make_pair(-1,-1);
            return make_pair(val,-min(h,n1-h));
        }


    return make_pair(-1,-1);
}

inline void Try(long long x2,long long y2,long long x1 ,long long y1){
    if(x1!=x2) ans = max(ans,y1-x1+y2-x2); else {
        x1+=d1; y1-=d1;
        if(x1<y1) ans = max(ans,y1-x1+y2-x2);
        x1-=d1; y1+=d1;

        x2+=d2; y2-=d2;
        if(x2<y2) ans = max(ans,y1-x1+y2-x2);
    }
}

int main()
{
    freopen("trapeze2.in","r",stdin);
    freopen("trapeze2.out","w",stdout);

    scanf("%lld %lld %lld",&x1,&d1,&n1); x1 <<= 1; d1 <<= 1;
    scanf("%lld %lld %lld",&x2,&d2,&n2); x2 <<= 1; d2 <<= 1;

    for(i=1,x=x2;i<=n2;i++,x+=d2){
        pair<long long,long> act = isKey(x);
        if(act.first==-1) continue;

        if(act.second>=0) drept++;
        long dim = min(i-1,n2-i);

        if(dim == 0 || act.second==0) continue;
        cnt += 1LL*dim*abss(act.second);

        if(act.second>0)
            Try(x-dim*d2,x+dim*d2 , x-act.second*d1,x+act.second*d1);
        else{
            act.second *= -1;
            Try(x-dim*d2,x+dim*d2 , x-act.second*d1+(d1>>1),x+act.second*d1-(d1>>1));
        }
    }
    for(i=1,x=x2+(d2>>1);i<n2;x+=d2,i++){
        pair<long long,long> act = isKey(x);
        if(act.first==-1) continue;
        long dim = min(i,n2-i);

        if(dim == 0 || act.second==0) continue;
        cnt += 1LL*dim*abss(act.second);

        if(act.second>0)
            Try(x-dim*d2+(d2>>1),x+dim*d2-(d2>>1) , x-act.second*d1,x+act.second*d1);
        else{
            act.second *= -1;
            Try(x-dim*d2+(d2>>1),x+dim*d2-(d2>>1) , x-act.second*d1+(d1>>1),x+act.second*d1-(d1>>1));
        }
    }

    cnt -= (drept*(drept-1))>>1;

    printf("%lld\n",cnt);
    printf("%lld\n",ans>>1);

    return 0;
}
