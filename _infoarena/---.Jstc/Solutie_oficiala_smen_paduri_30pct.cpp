#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

#define maxS 10000000
#define next nxt

long long A,B,Q,ans;
long i,addNow,n;
long nxt[maxS],a[maxS];
char s[maxS];
bitset<maxS> isIn;

int main()
{
    freopen("jstc.in","r",stdin);
    freopen("jstc.out","w",stdout);

    scanf("%lld %lld\n",&A,&B);
    fread(s,1,sizeof(s),stdin);

    for(i=0;s[i]!='\n';i++){
        if(s[i]=='I'){
            addNow++;
            nxt[addNow]=addNow; a[++n] = addNow;
            isIn[addNow]=true;
        } else
        if(s[i]=='E'){
            nxt[a[n]] = a[n]+1;
            isIn[a[n]]=false;
            n--;
        } else {
            Q = (A*Q+B)%addNow+1;
            if(isIn[Q]){ans+=Q;continue;}

            long tmp=Q;
            while(next[tmp]!=tmp && next[tmp]!=0) tmp=next[tmp];
            if(next[tmp]==0){ans--;continue;}
            ans += tmp;

            long Head = tmp;tmp=Q;
            while(next[tmp]!=tmp) {
                long ttmp = next[tmp];
                next[tmp]=Head;
                tmp = ttmp;
            }
        }
    }

    printf("%lld",ans);

    return 0;
}
