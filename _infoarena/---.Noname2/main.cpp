#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define abs abss
#define maxN 100111

long n,i,j,p;
vector<long long> V;
long long k,x,targ,opt,kk;
long Ans;

bool any,first;
long long Left[maxN],Right[maxN];

long long abss(long long a){
    if(a < 0) return -a;
    return a;
}

int main()
{
    freopen("noname2.in","r",stdin);
    freopen("noname2.out","w",stdout);

    scanf("%ld %lld",&n,&k);
    V.resize(n); kk = k;
    for(i=0;i<n;i++){
        scanf("%lld",&x);
        V[i] = x;
    }
    sort(V.begin(),V.end());

    for(i=1;i<n;i++) Left[i] = Left[i-1] + V[i] - V[i-1];
    for(i=n-2;i>=0;i--) Right[i] = Right[i+1] + V[i+1] - V[i];

    for(i=1;i<n;i++) Left[i] += Left[i-1] ;
    for(i=n-2;i>=0;i--) Right[i] += Right[i+1] ;

    i = 0; p = 0; j = 0;
    while(k-abs(V[j+1]-V[p]) >= 0){
        j++; k-= abs(V[j+1]-V[p]);
        if(j==n-1) break;
    }
    Ans = j-i+1;

    for(p=1;p<n;p++){
        if(j < p){
            i = p; j = p;
        }

        k = kk-(Left[j] - Left[p] - abs(V[p]-V[0])*(j-p) + Right[i]- Right[p] - abs(V[p]-V[n-1])*(p-i) );
        while(k < 0) k += abs(V[i++]-V[p]);
        if(j != p){
            targ = abs(V[p]-V[j+1]);
            while(i!=p && targ<abs(V[p]-V[i])) k += abs(V[p]-V[i++]);
        }

        any = true;
        while(any){
            any = false; opt = 1LL << 40;
            if(i!=0) opt = abs(V[p]-V[i-1]),first=true,any=true;
            if(j!=n-1)
                if(opt > abs(V[p]-V[j+1])){
                    opt = abs(V[p]-V[j+1]),first=false,any=true;
                }
            if(any){
                k -= opt;
                if(k<0){
                    k += opt;
                    break;
                }
                if(first) i--; else j++;
            }
        }

        Ans = max(Ans,j-i+1);
    }

    cout << Ans;

    return 0;
}
