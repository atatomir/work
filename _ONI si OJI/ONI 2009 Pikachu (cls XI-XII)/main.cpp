#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011

int n,i,k;
int a[maxN];
set<int> S;

int l,r;
set<int>::iterator mid;
ll sumLess,sumGreater,allSum;
ll ans=(1LL<<60);

void review(){
    while(l<r){
        l++; r--; mid++;
        sumLess += *mid;
        sumGreater -= *mid;
    }
    while(l>r){
        l--; r++ ;
        sumLess -= *mid;
        sumGreater += *mid;
        mid--;
    }
}
void check(){
    ll _mid = *mid;
    ll act = _mid*(l+1) - sumLess +
             sumGreater - _mid*r;
    ans = min(ans,act);
}

int main()
{
    freopen("pikachu.in","r",stdin);
    freopen("pikachu.out","w",stdout);

    scanf("%d%d",&n,&k);
    fordef(i,1,n) scanf("%d",&a[i]);
    S = set<int>(a+1,a+k+1);
    fordef(i,1,k) allSum += a[i];

    mid = S.begin(); l = 0; r = k-1;
    sumLess = *mid; sumGreater = allSum-sumLess;
    review(); check();

    fordef(i,k+1,n){
        int val = a[i];
        if(val<=*mid) {
            sumLess += val;
            l++;
        } else {
            sumGreater += val;
            r++;
        }
        S.insert(val);

        val = a[i-k];
        if(val<*mid) {
            sumLess -= val;
            l--;
        } else
        if(val>*mid){
            sumGreater -= val;
            r--;
        } else
        if(val == *mid){
            set<int>::iterator wh = mid; wh++;
            sumLess += *wh;
            sumGreater -= *wh;
            l++; r--;

            sumLess -= *mid;
            l--; mid = wh;
        }
        S.erase(val);

        review();check();
    }
    printf("%lld",ans);


    return 0;
}
