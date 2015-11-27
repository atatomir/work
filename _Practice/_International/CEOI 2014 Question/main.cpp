#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 920
#define maxBit 12

long pre[maxN + 20],cont;
long op,n,t;
long x,y,bit,h,v;

void preProcess(long bit,long need,long mask){
    if(bit == maxBit){
        pre[++cont] = mask;
        return;
    }
    if(need) preProcess(bit+1,need-1,mask | (1 << bit));
    if(maxBit-bit > need) preProcess(bit+1,need,mask);
}

int main()
{
    freopen("question.in","r",stdin);
    freopen("question.out","w",stdout);

    preProcess(0,6,0);
    sort(pre,pre+maxN+1);

    scanf("%ld\n%ld %ld",&op,&n,&t); n = maxN;
    if(op == 1){
        for(;t;t--){
            scanf("%ld %ld",&x,&y);
            x = pre[x]; y = pre[y];
            for(bit=0;;bit++)
                if((x & (1 << bit))&&((y & (1 << bit)) == 0)) break;
            printf("%ld\n",bit+1);
        }
    } else {
        for(;t;t--){
            scanf("%ld %ld",&v,&h);

            v = pre[v]; h--;
            if(v & (1 << h)) printf("YES\n"); else printf("NO\n");
        }
    }

    return 0;
}
