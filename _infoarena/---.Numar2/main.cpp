#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 111
#define maxVal 10011

int n,k,i,l,r,mid,lim,ans;
int v[maxN];

int cnt;
int vaj[maxVal];

void solve(int pos,int act,bool sel){
    if(pos==n+1){
        if(act==1) return;
        if(!sel) act = -act;
        if(cnt<maxVal)vaj[++cnt]=(act);

        return;
    }

    solve(pos+1,act,sel);
    if(act*v[pos]<=lim) solve(pos+1,act*v[pos],sel^true);
}
int getCount(int lim){
    ans = 0;
    int i;

    fordef(i,1,cnt){
        int act = vaj[i];
        int def = (act<0?-act:act);

        def = lim/def;
        if(act<0) ans -= def;
        else      ans += def;
    }

    return ans;
}

int main()
{
    freopen("numar2.in","r",stdin);
    freopen("numar2.out","w",stdout);

    scanf("%d%d",&n,&k);
    fordef(i,1,n) scanf("%d",&v[i]);

    lim = v[1]*k;
    solve(1,1,false);

    l=1;r=lim;
    while(l<=r){
        mid = (l+r)>>1;
        if( getCount(mid) < k )
            l = mid+1;
        else
            r = mid-1;
    }
    printf("%d",l);

    return 0;
}
