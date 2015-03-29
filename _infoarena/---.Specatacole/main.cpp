#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
 
#define maxN 2011
#define room first
#define start second.first
#define stop second.second
#define maxM 20011
 
typedef pair<long,pair<long,long> > Show;
 
long n,m,i,j,pos;
long A[maxN],B[maxN];
vector<Show> Shows;
long dp[maxM],sdp[maxN];
 
vector<pair<long,long> > Last[maxN];
 
bool cmp(const Show& a,const Show& b){
    return a.stop < b.stop;
}
 
long cb(long x){
    long i=1,j=m,mid;
    do{
        mid = (i+j)>>1;
        if(x < Shows[mid].stop)
            j = mid-1;
        else
            i = mid+1;
    } while(i<=j);
    return j;
}
 
long getVal(long myRoom,long x){
    if(Last[myRoom].empty()) return 0;
 
    long best = 0;
    for(long i=0;i<Last[myRoom].size();i++){
            if(Last[myRoom][i].first <= x) best = max(best,Last[myRoom][i].second);
    } return best;
}
 
int main()
{
    freopen("spectacole.in","r",stdin);
    freopen("spectacole.out","w",stdout);
 
    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%ld",&A[i]);
    for(i=1;i<=n;i++) scanf("%ld",&B[i]);
 
    Shows.resize(m+1);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&Shows[i].room,&Shows[i].start,&Shows[i].stop);
        Shows[i].stop += A[Shows[i].room];
    }
    sort(Shows.begin(),Shows.end(),cmp);
 
    for(i=1;i<=m;i++){
        pos = cb(Shows[i].start - B[Shows[i].room]); if(pos == i) pos--;
        dp[i] = max(sdp[pos]+1,getVal(Shows[i].room,Shows[i].start)+1);
        sdp[i] = max(sdp[i-1],dp[i]);
 
        Last[Shows[i].room].push_back(make_pair(Shows[i].stop - A[Shows[i].room],dp[i]));
    }
 
    printf("%ld",sdp[m]);
 
    return 0;
}