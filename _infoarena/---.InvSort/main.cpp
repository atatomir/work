#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <assert.h>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back

#define maxN 32011
#define answer(x,y) printf("%d %d\n",x,y)
//#define DEBUG

int n,i;
int v[maxN];
int rez[maxN];

int cnt;

bool sorted(int l,int r){
    for(int i=l+1;i<=r;i++)
        if(v[i] < v[i-1]) return false;
    return true;
}

void Invert(int l,int r){
    answer(l,r);

    /**/ cnt += r-l+1;

    while(l<r){
        swap(v[l],v[r]);
        l++; r--;
    }
}

void Merge(int l,int r,int lim){
    if( sorted(l,r) ) return;

    int mid = (l+r)>>1;
    Merge(l,mid,lim);
    Merge(mid+1,r,lim);

    int ll = r+1, rr = l-1,i;
    fordef(i,l,mid)
        if(v[i] > lim) ll = min(ll,i);
    fordef(i,mid+1,r)
        if(v[i] <= lim) rr = i;

    if(ll>rr) return;
    Invert(ll,rr);
}

void solve(int l,int r){
    if(l>=r) return;
    if(sorted(l,r)) return;
    int i;
    int mid = (l+r)>>1;
    int lim = rez[mid];
    if(rez[mid] == rez[r]) lim--;

    Merge(l,r,lim);

    mid = r;
    fordef(i,l+1,r){
        if( v[i-1]<=lim && v[i]>lim ){
            mid = i-1;
            break;
        }
    }

    solve(l,mid);
    solve(mid+1,r);
}

int main()
{
    freopen("invsort.in","r",stdin);
    freopen("invsort.out","w",stdout);

    scanf("%d",&n);
    fordef(i,1,n) {scanf("%d",&v[i]); rez[i] = v[i];}

    //!----------------------------------
    #ifdef DEBUG
        srand(time(NULL));
        n = 32000;
        fordef(i,1,n) v[i]=rez[i]=rand()%n;
    #endif
    //!----------------------------------

    sort(rez+1,rez+n+1);

    solve(1,n);

    //!----------------------------------
    #ifdef DEBUG
        //fordef(i,1,n) cerr << v[i] << ' '; cerr << '\n';
        cerr << cnt << '\n';
        if(cnt > 4000000) cerr << "Nu iei maxim!\n";
        fordef(i,1,n) assert(v[i]==rez[i]);
    #endif
    //!----------------------------------

    return 0;
}
