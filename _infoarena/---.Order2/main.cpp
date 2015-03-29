#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 2048

struct Elem{
    long val,pos;
};
bool cmp(const Elem& a,const Elem& b){return a.val<b.val;}

long n,i,cnt;
long v[maxN];
Elem e[maxN];
long pos[maxN];

void Invert(long act){
    cnt++;
    if(cnt<2*n)printf("%ld\n",act);
    long i,j,t;

    i=1;j=act-1;
    while(i<j){
        pos[v[i]] = j;
        pos[v[j]] = i;
        t=v[i];v[i]=v[j];v[j]=t;
        i++;j--;
    }
    i=act+1;j=n;
    while(i<j){
        pos[v[i]] = j;
        pos[v[j]] = i;
        t=v[i];v[i]=v[j];v[j]=t;
        i++;j--;
    }
}

int main()
{
    freopen("order2.in","r",stdin);
    freopen("order2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&e[i].val);
        e[i].pos=i;
    }
    sort(e+1,e+n+1,cmp);
    for(i=1;i<=n;i++) {
        v[e[i].pos] = i;
        pos[i] = e[i].pos;
    }

    for(i=1;i<=n;i++){
        Invert(pos[i]);
        Invert(pos[i]+1);
    }

    return 0;
}
