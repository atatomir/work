#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 5005
#define maxDef 100000001

long n,i,answer,h;
long a[maxN],l[maxN],r[maxN],preL[maxN],preR[maxN];
long first,mid,last,localFirst,localLast;

long Try(long bg,long en,long put){
    long i,minim=maxDef,maxim=-1,local;

    if(put == 2){
        for(i=bg;i<=en;i++){
            if(a[i] < minim) minim = a[i];
            if(a[i] > maxim) maxim = a[i];
            l[i] = maxim-minim;
        }
    }

    minim = maxDef; maxim = -1;

    if(put == 1){
        for(i=en;i>=bg;i--){
            if(a[i] < minim) minim = a[i];
            if(a[i] > maxim) maxim = a[i];
            r[i] = maxim-minim;
        }
    }

    long answer = 0,h;

    if(put == 1)
    for(i=bg+1;i<=en-2;i++){
        h = preL[i] + r[i+1];
        if(h > answer) {
            answer = h;
            local = i;
        }
    }

    if(put == 2)
    for(i=bg+1;i<=en-2;i++){
        h = l[i] + preR[i+1];
        if(h > answer) {
            answer = h;
            local = i;
        }
    }

    if(put == 1) localFirst = local; else localLast = local;

    return answer;
}

void preCalc() {
    long minim=maxDef,maxim=-1;
    for(i=1;i<=n;i++){
        if(a[i] < minim) minim = a[i];
        if(a[i] > maxim) maxim = a[i];
        preL[i] = maxim-minim;
    }

    minim = maxDef; maxim = -1;
    for(i=n;i;i--){
        if(a[i] < minim) minim = a[i];
        if(a[i] > maxim) maxim = a[i];
        preR[i] = maxim-minim;
    }
}

int main()
{
    freopen("split.in","r",stdin);
    freopen("split.out","w",stdout);

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);

    preCalc();

    for(i=4;i<=n-4;i++){
        h = Try(1,i,1) + Try(i+1,n,2);
        if(h > answer) {
            answer = h;
            first = localFirst;
            mid = i;
            last = localLast;
        }
    }

    printf("%ld\n%ld %ld %ld\n",answer,first,mid,last);

    return 0;
}
