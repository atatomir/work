#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<long,long> plic;

#define mp make_pair
#define x first
#define y second
#define maxN 100010

long n,i;
vector<plic> v;
plic tmp;
long dp[maxN];

bool cmp(const plic& a,const plic& b){
    if(a.x == b.x) return a.y > b.y;
    return a.x < b.x;
}

long cb(long x){
    long i=1,j=dp[0],m;
    while(i<=j){
        m = (i+j)/2;
        if(x <= dp[m])
            j = m-1;
        else
            i = m+1;
    }
    return i;
}

int main()
{
    freopen("plicuri.in","r",stdin);
    freopen("plicuri.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&tmp.x,&tmp.y);
        if(tmp.x > tmp.y){long t=tmp.x;tmp.x=tmp.y;tmp.y=t;}
        v.push_back(tmp);
    }
    sort(v.begin(),v.end(),cmp);

    dp[0] = 1; dp[1] = v[0].y;
    for(i=1;i<v.size();i++){
        long pos = cb(v[i].y);
        if(pos > dp[0]) dp[0]++;
        dp[pos] = v[i].y;
    }

    printf("%ld",dp[0]);

    return 0;
}
