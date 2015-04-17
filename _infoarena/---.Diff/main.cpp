#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100024
#define nope printf("-1\n")

struct Answer{
    long how,wh;
    Answer(){};
    Answer(long _how,long _wh){
        how=_how; wh=_wh;
    }
};

long n,m,i,x;
long a[maxN],mMax[maxN],mMin[maxN];
Answer ansMin,ansMax;
long ansLow[maxN],ansHigh[maxN];
pair<long,long> AnsZero;

int main()
{
    freopen("diff.in","r",stdin);
    freopen("diff.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);
        if(a[i]==0) a[i]=-1;
        a[i] += a[i-1];
    }

    mMin[n]=mMax[n]=a[n];
    for(i=n-1;i;i--){
        mMin[i] = min(mMin[i+1],a[i]);
        mMax[i] = max(mMax[i+1],a[i]);
    }

    ansMin.how=ansMax.how = -1;
    for(i=0;i<n;i++){
        long tmp;

        tmp = mMax[i+1] - a[i];
        if(tmp > ansMax.how) ansMax = Answer(tmp,i+1);

        tmp = a[i] - mMin[i+1];
        if(tmp > ansMin.how) ansMin = Answer(tmp,i+1);
    }

    AnsZero=make_pair(-1,-1);

    long tmp=0;
    for(i=ansMax.wh;i<=n;i++){
        tmp += (a[i]-a[i-1]);
        if(tmp>0)ansHigh[tmp] = i;
        if(tmp==0) AnsZero = make_pair(ansMax.wh,i);
    }

    tmp = 0;
    for(i=ansMin.wh;i<=n;i++){
        tmp += (a[i]-a[i-1]);
        if(tmp<0)ansLow[-tmp] = i;
        if(tmp==0) AnsZero = make_pair(ansMin.wh,i);
    }

    for(i=1;i<=m;i++){
        scanf("%ld",&x);
        if(x < -n || x > n) {nope;continue;}
        if(x==0) {
            if(AnsZero.first==-1) nope;
            else                  printf("%ld %ld\n",AnsZero.first,AnsZero.second);
        }
        if(x>0){
            if(ansHigh[x]==0) nope;
            else               printf("%ld %ld\n",ansMax.wh,ansHigh[x]);
        }
        if(x<0){
            if(ansLow[-x]==0) nope;
            else               printf("%ld %ld\n",ansMin.wh,ansLow[-x]);
        }
    }

    return 0;
}
