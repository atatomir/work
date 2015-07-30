#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxN 1000011

long n,x,tmp,i;
char s[maxN];
char ans[maxN];

struct cmp{
    bool operator()(long a,long b){
        if(s[a]==s[b]) return a > b;
        return (s[a]<s[b]);
    }
};
priority_queue<long,vector<long>,cmp> PQ;
bool inPQ[maxN];
long aib[maxN];

inline long zeros(long x){
    return (x^(x-1))&x;
}
void aAdd(long x){
    while(x<=n){
        aib[x]++;
        x += zeros(x);
    }
}
long aSum(long x){
    long ans=0;
    while(x){
        ans += aib[x];
        x -= zeros(x);
    }
    return ans;
}

inline void addNext(){
    if(tmp>n) return;
    tmp++;
    while(s[tmp]=='@' || inPQ[tmp]) tmp++;
    if(tmp>n) return;

    PQ.push(tmp);
    inPQ[tmp] = true;
}

int main()
{
    freopen("bignumber.in","r",stdin);
    freopen("bignumber.out","w",stdout);

    scanf("%ld %ld\n%s\n",&n,&x,s+1);
    tmp = min(n,x+1);
    for(i=1;i<=tmp;i++) {PQ.push(i);inPQ[i]=true;}

    for(i=1;i<=n;i++){
        long id = PQ.top(); PQ.pop(); inPQ[id] = false;
        long pos = id - aSum(id-1);

        while((x+1<pos) || (s[id]=='@')){
            tmp = min(tmp,id-1);
            id = PQ.top(); PQ.pop();
            pos = id - aSum(id-1);
            inPQ[id] = false;
        }

        if(pos==1){
            ans[i] = s[id];
            addNext();
            aAdd(id);
            s[id]='@';
        } else {
            x -= pos-1;
            aAdd(id);
            ans[i]=s[id];
            s[id]='@';
        }
    }

    printf("%s",ans+1);

    return 0;
}
