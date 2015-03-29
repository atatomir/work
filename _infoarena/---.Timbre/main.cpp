#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define maxN 1011
#define m first
#define c second

typedef pair<long,long> mPair;

long n,m,k,i,ans;
vector<mPair> intr;

struct cmp{
    bool operator()(long a,long b){
        return a>b;
    }
};

priority_queue<long,vector<long>,cmp> H;

int main()
{
    freopen("timbre.in","r",stdin);
    freopen("timbre.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=m;i++){
        mPair tmp;
        scanf("%ld %ld",&tmp.m,&tmp.c);
        intr.push_back(tmp);
    }
    sort(intr.begin(),intr.end());

    i = n;
    while(i){
        while(!intr.empty()){
            if(intr[intr.size()-1].m < i) break;
            H.push(intr[intr.size()-1].c);
            intr.pop_back();
        }

        long cost = H.top(); H.pop();
        ans += cost;
        i-= k; if(i<0) i=0;
    }

    printf("%ld",ans);

    return 0;
}
