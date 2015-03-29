#include <iostream>
#include <cstdio>

using namespace std;

#define maxSet 4000000
#define maxS 10000000

struct mySet{
    long beg,cnt;
};

long long A,B,Q,ans;
long i,addNow,n;
mySet act[maxSet];
char s[maxS];

bool isIn[maxS];

long getSet(){
    long i=1,j=n,m;
    while(i<=j){
        m = (i+j)>>1;
        if(Q<act[m].beg)
            j = m-1;
        else
            i = m+1;
    }
    return j;
}

int main()
{
    freopen("jstc.in","r",stdin);
    freopen("jstc.out","w",stdout);

    scanf("%lld %lld\n",&A,&B);
    fread(s,1,sizeof(s),stdin);

    act[0].beg = -17;
    for(i=0;s[i]!='\n';i++){
        if(s[i]=='I'){
            addNow++; isIn[addNow]=true;
            if(addNow == act[n].beg+act[n].cnt) {act[n].cnt++;continue;}
            act[++n].beg=addNow; act[n].cnt=1;
        } else
        if(s[i]=='E'){
            isIn[act[n].beg+act[n].cnt-1]=false;
            act[n].cnt--; if(act[n].cnt==0) n--;
        } else {
            Q = (A*Q+B)%addNow+1;
            if(isIn[Q]){ans+=Q;continue;}
            long mySet = getSet();
            if(mySet==0) ans--; else
            if(Q<act[mySet].beg+act[mySet].cnt) ans += Q; else{
                if(mySet==n) ans--; else ans += act[mySet+1].beg;
            }

        }
    }

    printf("%lld",ans);

    return 0;
}
