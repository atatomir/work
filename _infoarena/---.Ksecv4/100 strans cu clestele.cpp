#include <iostream>
#include <cstdio>
#include <vector>
 
using namespace std;
#define maxN 1000011
 
#define maxM 2500
#define v V
#define lSon (node<<1)
#define rSon ((node<<1)|1)
#define isGood(maxi,mini,limi) (maxi+mini+1)/2<=lim
 
//long long tmp[maxN];
 
 
int n,m,i,k;
 
long long A[maxM],B[maxM];
long long V[maxN];
 
long long l,r,mid;
long long vmin[maxN<<2],vmax[maxN<<2];
 
 
template <class T>
T FastMax(const T& left, const T& right)
{
    return left > right ? left : right;
}
//aint aMax,aMin;
 
//! ---------search in tree----------------
/**/long long preMin,preMax;
/**/vector<long> wh;
/**/vector<pair<long,long> > vaj;
/**/long whAns;
 
void query(long node,long l,long r,long qL,long qR){
    if(qL<=l&&r<=qR) {
        wh.push_back(node);
        vaj.push_back(make_pair(l,r));
        return;
    }
 
    long mid = (l+r)>>1;
    if(qL<=mid) query(lSon,l,mid,qL,qR);
    if(qR> mid) query(rSon,mid+1,r,qL,qR);
}
 
bool trySolve(long node,long l,long r,long long lim){
    long long mmin = FastMax(preMin, vmin[ node ] );
    long long mmax = FastMax(preMax, vmax[ node ] );
 
    if(isGood(mmax,mmin,lim)){
        preMin = mmin;
        preMax = mmax;
        whAns = r;
 
        return true;
    } else {
        if(l==r) return false;
        long mid  = (l+r)>>1;
 
        if( trySolve(lSon,l,mid,lim) )
            trySolve(rSon,mid+1,r,lim);
 
 
        return false;
    }
}
long seeWhere(long start,long long lim){
    whAns=start;
 
    wh.clear(); vaj.clear();
 
    query(1,1,n,start,n);
    preMin = preMax = -(1LL<<61);
    //! acum am toate nodurile necesare in vector
 
    for(long i=0;i<wh.size();i++){
        if(trySolve(wh[i],vaj[i].first,vaj[i].second,lim)) /*whAns = vaj[i].second*/; else break;
    }
 
    return whAns;
}
 
//! -----------------------------------------
 
bool good(long long lim){
    long pos=1;
 
    if(lim < 100){
        lim++; lim--;
    }
 
    for(int i=1;i<=k;i++){
        preMin = preMax = -(1LL<<61);
        long wh = seeWhere(pos,lim);
        pos = wh+1;
 
        if(pos==n+1) return true;
    }
 
    return false;
}
 
 
 
 void makeTree(long node,long l,long r){
            if(l==r) {
                vmax[node] = V[l];
                vmin[node] = -V[l];
                return ;
            }
 
            long mid = (l+r)>>1;
            makeTree(lSon,l,mid);
            makeTree(rSon,mid+1,r);
 
            vmax[node] = FastMax(vmax[lSon],vmax[rSon]);
            vmin[node] = FastMax(vmin[lSon],vmin[rSon]);
 
}
 
 
int main()
{
    freopen("ksecv4.in","r",stdin);
    freopen("ksecv4.out","w",stdout);
 
    scanf("%d %d %d",&n,&k,&m);
    for(i=0;i<m;i++) scanf("%lld",&A[i]);
    for(i=0;i<m;i++) scanf("%lld",&B[i]);
 
    for(i=0;i<n;i++) V[i+1] = A[i%m] ^ B[i/m];
 
    //for(i=1;i<=n;i++) tmp[i] = V[i];
    //aMax.init(vmax,vmin,n);
    //for(i=1;i<=n;i++) tmp[i] *= -1;
    //aMin.init(vmin,n);
 
    makeTree(1,1,n);
 
 
    //l=0; r = (1LL<<61)+1;
    l = 0; r = (vmax[1] + vmin[1] + 1)/2;
    while(l<=r){
        mid = (l+r)>>1;
        if( good(mid) )
            r = mid-1;
        else
            l = mid+1;
    }
 
    printf("%lld",l);
    //cerr << l<<'\n';
 
    return 0;
}
